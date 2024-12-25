#ifndef ABILITY_H
#define ABILITY_H
#include "../field/PlayingField.h"
#include "../ships/ShipManager.h"

class Ability {
public:
    virtual bool apply(PlayingField& field, ShipManager& manager, int x, int y) = 0;
    virtual ~Ability(){}
};


#endif