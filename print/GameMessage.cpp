#include "GameMessage.h"

void GameMessage::messageWelcome(){
    std::cout << WELCOME << std::endl;
}

void GameMessage::messageForShipPlacement(int length){
    std::cout << PLACE << length << std::endl;
    std::cout << SHIP_LAYOUT;
}

void GameMessage::messageForEnteringCoords(){
    std::cout << ENTER_COORDINATES;
}

void GameMessage::messageForAbilityUse(){
    std::cout << ABILITIES;
}
void GameMessage::messageForDoubleDamageUse(){
    std::cout << DOUBLE_DAMAGE_TEXT << std::endl;
    std::cout << HIT_COORDINATES;
}

void GameMessage::messageForShellingUse(){
    std::cout << SHELLING_TEXT << std::endl;
}
void GameMessage::messageForScannerUse(){
    std::cout << SCANNER_TEXT << std::endl;
    std::cout << SCAN_COORDINATES;
}

void GameMessage::messageForAnswerScanner(bool answer){
    if (answer){
        std::cout << SCAN_POSITIVE << std::endl;
    }else{
        std::cout << SCAN_NEGATIVE << std::endl;
    }
}

void GameMessage::messageForGameEnd(bool answer){
    if (answer){
        std::cout << WINING << std::endl;
    }else{
        std::cout << LOSING << std::endl;
    }
}
void GameMessage::message(Ship* ship){
    std::cout << "Segment hp" << ship->getSegments()[0]->getValue() << std::endl;
}

void GameMessage::messageForPrevSave(){
    std::cout << PREV_SAVE;
}

void GameMessage::messageForSaveOrLoad(){
    std::cout << SAVE_LOAD;
}

void GameMessage::messageForSave(){
    std::cout << SAVE;
}
