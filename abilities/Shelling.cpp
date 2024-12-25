#include "Shelling.h"
#include <iostream>

bool Shelling::apply(PlayingField& field, ShipManager& manager, int x, int y) {
    srand(time(NULL));
    Ship* ship = nullptr;
    short randomNumber;
    std::vector<Ship*> ships = manager.getShips();
    int shipCount = manager.getShipCount();
    do {
        randomNumber = rand()%shipCount;
        ship = ships[randomNumber];
    } while (ship->isDestroyed());
    std::vector<Segment*>& shipSegments = ship->getSegments();
    do {
        randomNumber = rand()%(ship->getLength());
    } while (shipSegments[randomNumber]->getValue() == DESTROYED);
    ship->hitSegment(randomNumber);
    shipSegments[randomNumber]->setFlagHitByShelling(true);
    //std::cout << "\nHit ship with length " << ship->getLength() << " and segment" << randomNumber << '\n';
    return true;
}