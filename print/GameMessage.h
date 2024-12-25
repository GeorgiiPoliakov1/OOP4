#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H
#include <iostream>
#include "../ships/Ship.h"
#define WELCOME "Hello, you have launched Sea Battle."
#define PLACE "Where do you want to place ship with length - "
#define SHIP_LAYOUT "Enter ship`s layout (0 - HORIZONTAL, 1 - VERTICAL): "
#define PREV_SAVE "You have a save from a previous game. Want to go back to it? (1 - Yes): "
#define SAVE_LOAD "Do you want to save the game or load previous save? (2 - save game, 1 - load game): "
#define SAVE "Do you want to save the game? (1 - Yes): "
#define ENTER_COORDINATES "Enter x y: "
#define PLACE_ERROR "You can`t place ship there. Try again!"
#define ABILITIES "Enter x, y coordinates for ability use: "
#define DOUBLE_DAMAGE_TEXT "You`re lucky! You have got double damage."
#define SHELLING_TEXT "You`re lucky! You have got shelling. Some enemy ship took damage!"
#define SCANNER_TEXT "You`re lucky! You have got scanner."
#define HIT_COORDINATES "Enter x y to hit: "
#define SCAN_COORDINATES "Enter x y to scan: "
#define SCAN_POSITIVE "There is a ship in this area!"
#define SCAN_NEGATIVE "There is no ship in this area :("
#define WINING "Congratulations! You won the game!"
#define LOSING "You lost, better luck next time."

class GameMessage{
 public:
    void messageWelcome();
    void messageForShipPlacement(int length);
    void messageForAbilityUse();
    void messageForDoubleDamageUse();
    void messageForShellingUse();
    void messageForScannerUse();
    void messageForEnteringCoords();
    void messageForAnswerScanner(bool answer);
    void messageForPrevSave();
    void messageForSaveOrLoad();
    void messageForNoLoad();
    void messageForSave();
    void messageForGameEnd(bool answer);
    void message(Ship* ship);
};
#endif