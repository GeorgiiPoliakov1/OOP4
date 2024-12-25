#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "Ability.h"

class DoubleDamage : public Ability {
public:
    bool apply(PlayingField& field, ShipManager& manager, int x, int y) override;
};

#endif