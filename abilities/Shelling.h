#ifndef SHELLING_H
#define SHELLING_H

#include "Ability.h"

class Shelling : public Ability {
public:
    bool apply(PlayingField& field, ShipManager& manager, int x, int y) override;
};

#endif