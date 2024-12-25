#ifndef DRAWING_FIELD_H
#define DRAWING_FIELD_H
#include "../field/PlayingField.h"
#define ENEMYFIELD "ENEMY`S FIELD" 
#define YOURFIELD "YOUR FIELD"
class FieldDrawer{
public:
    FieldDrawer();
    void printPlayingField(PlayingField field, bool isEnemyField);
};
#endif