#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"

class Scanner : public Ability {
public:
    bool apply(PlayingField& field, ShipManager& manager, int x, int y) override;
};

#endif