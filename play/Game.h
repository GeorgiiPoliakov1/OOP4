#ifndef GAME_H
#define GAME_H
#include <vector>
#include "../field/PlayingField.h"
#include "../abilities/AbilityManager.h"
#include "../ships/ShipManager.h"
#include "../print/GameMessage.h"
#include "../print/InputHandler.hpp"
#include "../print/CommandHandler.h"
#include "../print/FieldDrawer.h"
#include "../save/GameState.h"

enum GameStatus{
    EXIT = 3,
    WIN = 2,
    LOSS = 1,
    IN_PROGRESS = 0,
    NOT_STARTED = -1
};

class Game {
public:
    Game(); 
    void arrangeUserShips();
    void arrangeEnemyShips();
    void makeUserMove(int x, int y);
    void makeComputerMove();
    bool applyAbility(int x, int y);
    GameStatus getGameStatus();
    void saveGame();
    void loadGame();
    vector<int> getShipSettings(){ return shipSettings;};
    pair<int, int> getFieldSettings(){return fieldSettings;};
    bool checkSave(){ return gameState.checkSave();};
private:
    PlayingField userField;
    PlayingField enemyField;
    AbilityManager abilityManager;
    ShipManager userShipManager;
    ShipManager enemyShipManager;
    GameMessage gameMessage;
    FieldDrawer drawingField = FieldDrawer();
    InputHandler<CommandHandler> inputHandler;
    GameState gameState;
    GameStatus gameStatus = NOT_STARTED;
    vector<int> shipSettings = {1,2,3,4};
    pair<int, int> fieldSettings = {7, 7};

};

#endif