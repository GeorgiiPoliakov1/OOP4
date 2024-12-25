#include "DoubleDamage.h"

bool DoubleDamage::apply(PlayingField& field, ShipManager& manager, int x, int y) {
    field.hitCell(x,y,true, false);
    return true;
}