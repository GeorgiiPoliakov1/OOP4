#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "../abilities/AbilityManager.h"
#include "../ships/ShipManager.h"
#include "FileHandler.h"
#include "../print/GameMessage.h"
#include <fstream>
using namespace std;
using json = nlohmann::json;
class GameState {
private:
    string filename;
    json savedData;

public:
    GameState(const string& fname) : filename(fname) { }
    void save(PlayingField& userField, PlayingField& enemyField, ShipManager& userShipManager, ShipManager& enemyShipManager, AbilityManager& abilityManager);
    void load(PlayingField& userField, PlayingField& enemyField, ShipManager& userShipManager, ShipManager& enemyShipManager, AbilityManager& abilityManager);
    void writeState();
    bool checkSave();
    bool is_file_written() const;
    friend ostream& operator<<(ostream& stream, const GameState& gameState);
    friend istream& operator>>(istream& stream, GameState& gameState);

};

#endif