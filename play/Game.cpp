#include "Game.h"


Game::Game(): userField(fieldSettings.first, fieldSettings.second), enemyField(fieldSettings.first, fieldSettings.second), userShipManager(shipSettings.size(), shipSettings), enemyShipManager(shipSettings.size(), shipSettings), gameState("gameData"){}


void Game::arrangeUserShips(){
    userShipManager = ShipManager(shipSettings.size(), shipSettings);
    userField = PlayingField(fieldSettings.first, fieldSettings.second);
    std::vector<Ship*>& userShips = userShipManager.getShips();
    drawingField.printPlayingField(userField, false);
    for (int index = 0; index < userShips.size(); index++){
        std::pair<Layout, std::pair <size_t, size_t>> shipFromUser = inputHandler.readShipFromUser(shipSettings[index]);
        if  (!(userField.placeShip(userShips[index], shipFromUser.first, shipFromUser.second.first, shipFromUser.second.second, false))){
            index--;
        }
        drawingField.printPlayingField(userField, false);
    }
}
void Game::arrangeEnemyShips(){
    srand(static_cast<unsigned int>(time(NULL)));
    enemyShipManager = ShipManager(shipSettings.size(), shipSettings);
    enemyField = PlayingField(fieldSettings.first, fieldSettings.second);
    std::vector<Ship*>& enemyShips = enemyShipManager.getShips();
    int shipsPlaced = 0;
    int width = enemyField.getWidth();
    int height = enemyField.getHeight();
    int x,y,layout;
    for (int index = 0; index < enemyShips.size(); index++){
        layout = rand()%2;
        x = rand() % width;
        y = rand() % height;
        while (enemyField.placeShip(enemyShips[index], static_cast<Layout>(layout), x, y, true)!=true)
        {
            x = rand() % width;
            y = rand() % height;
        }
    }
    drawingField.printPlayingField(userField, false);
    drawingField.printPlayingField(enemyField, true);
    gameStatus = IN_PROGRESS;
    
}
void Game::makeUserMove(int x, int y){
    enemyField.hitCell(x,y, false, false);
    if (enemyShipManager.isShipWasDestroyed()){
        abilityManager.addNewRandomAbility();
    }
    this->makeComputerMove();
}

void Game::makeComputerMove(){
    srand(static_cast<unsigned int>(time(NULL)));
    int width = userField.getWidth();
    int height = userField.getHeight();
    int x = rand() % width;
    int y = rand() % height;
    userField.hitCell(x,y, false, true);
    drawingField.printPlayingField(userField, false);
    drawingField.printPlayingField(enemyField, true);
}
bool Game::applyAbility(int x, int y){
    bool isDoubleDamageUsed = false;
    AbilityNames name = abilityManager.getFrontAbilityName();
    if (name == DOUBLE_DAMAGE){
        gameMessage.messageForDoubleDamageUse();
        abilityManager.applyAbility(enemyField, enemyShipManager, x, y);
        isDoubleDamageUsed = true;
    }else if (name == SHELLING){
        gameMessage.messageForShellingUse();
        abilityManager.applyAbility(enemyField, enemyShipManager, -1, -1);
    }else if (name == SCANNER){
        gameMessage.messageForScannerUse();
        if (abilityManager.applyAbility(enemyField, enemyShipManager, x, y)){
            gameMessage.messageForAnswerScanner(true);
        }else{
            gameMessage.messageForAnswerScanner(false);
        }
    }
    if (enemyShipManager.isShipWasDestroyed()){
        abilityManager.addNewRandomAbility();
    }
    if (isDoubleDamageUsed){
        this->makeComputerMove();
    }
    return isDoubleDamageUsed;
}
GameStatus Game::getGameStatus(){
    if (gameStatus == IN_PROGRESS){
        return IN_PROGRESS;
    }
    if (enemyShipManager.isAllShipsDestroyed() && gameStatus != NOT_STARTED){
        return WIN;
    }
    if (userShipManager.isAllShipsDestroyed() && gameStatus != NOT_STARTED){
        return LOSS;
    }
    return NOT_STARTED;
    
}
void Game::saveGame() { 
    if (gameStatus == NOT_STARTED){
        std::cerr << "You have nothing to save" << std::endl;
    }else{
        gameState.save(userField, enemyField, userShipManager, enemyShipManager, abilityManager); 
    }
}

void Game::loadGame() { 
    try{
        gameState.load(userField, enemyField, userShipManager, enemyShipManager, abilityManager); 
    }catch (runtime_error& exception){
        std::cerr << "You currently have no saves" << std::endl;
        return;
    }
    drawingField.printPlayingField(userField, false);
    drawingField.printPlayingField(enemyField, true);
    gameStatus = IN_PROGRESS;
}