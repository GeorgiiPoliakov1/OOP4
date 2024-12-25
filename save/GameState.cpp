#include "GameState.h"

void GameState::save(PlayingField& userField, PlayingField& enemyField, ShipManager& userShipManager, ShipManager& enemyShipManager, AbilityManager& abilityManager) {
    json jsonFile;
    jsonFile["userField"] = userField.toJson();
    jsonFile["enemyField"] = enemyField.toJson();
    jsonFile["abilityManager"] = abilityManager.toJson();
    FileHandler fileHandler(filename);
    fileHandler.openForWrite();
    fileHandler.write(jsonFile);
}
bool GameState::is_file_written() const {
    std::ifstream file(filename);
    return file.peek() != std::ifstream::traits_type::eof();
}
void GameState::load(PlayingField& userField, PlayingField& enemyField, ShipManager& userShipManager, ShipManager& enemyShipManager, AbilityManager& abilityManager) {
    FileHandler fileHandler(filename);
    fileHandler.openForRead();
    json jsonFile;
    fileHandler.read(jsonFile);
    userField = userField.fromJsonField(jsonFile["userField"]);
    enemyField = enemyField.fromJsonField(jsonFile["enemyField"]);
    userField.fromJsonCoordinates(jsonFile["userField"]); 
    enemyField.fromJsonCoordinates(jsonFile["enemyField"]);
    userShipManager.fromJson(jsonFile["userField"]);
    enemyShipManager.fromJson(jsonFile["enemyField"]);
    abilityManager.fromJson(jsonFile["abilityManager"]);
    std::vector<Ship*>& userShips = userShipManager.getShips();
    int width = userField.getWidth();
    int height = userField.getHeight();
    for (int i = 0; i < userShips.size(); i++){
        int coordinate = jsonFile["userField"]["ships"][i][0];
        int y = coordinate/width;
        int x = coordinate-y*width;
        userField.placeShip(userShips[i], userShips[i]->getLayout(), x, y, true);
    }
    std::vector<Ship*>& enemyShips = enemyShipManager.getShips();
    width = enemyField.getWidth();
    height = enemyField.getHeight();
    for (int i = 0; i < enemyShips.size(); i++){
        int coordinate = jsonFile["enemyField"]["ships"][i][0];
        int y = coordinate/width;
        int x = coordinate-y*width;
        enemyField.placeShip(enemyShips[i], enemyShips[i]->getLayout(), x, y, true);
    }
}

void GameState::writeState() {
    FileHandler fileHandler(filename);
    fileHandler.openForWrite();
    fileHandler.write(savedData);
}

bool GameState::checkSave(){
    try{
        FileHandler fileHandler(filename);
        fileHandler.openForRead();
    }catch(runtime_error& exception){
        return false;
    }
    return true;
    
}

ostream& operator<<(ostream& stream, const GameState& gameState) {
    FileHandler fileHandler(gameState.filename);
    fileHandler.openForRead();
    json jsonFile;
    fileHandler.read(jsonFile);
    stream << jsonFile.dump(4) << endl;
    return stream;
}
istream& operator>>(istream& stream, GameState& gameState) {
    json jsonFile;
    stream >> jsonFile; 
    gameState.savedData = jsonFile;
    if (jsonFile.is_null()) {
        throw runtime_error("Failed to read valid JSON data.");
    }
    gameState.writeState();
    return stream;
}