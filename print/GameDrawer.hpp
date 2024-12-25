#ifndef GAME_DRAWER_H
#define GAME_DRAWER_H
#include "../field/PlayingField.h"

template <typename FieldDrawerTemp>
class GameDrawer
{
 public:
    GameDrawer();
    void drawFields(PlayingField userShipManager, PlayingField enemyShipManager);
 private:
    FieldDrawerTemp fieldDrawer;
};

template <typename FieldDrawerTemp>
GameDrawer<FieldDrawerTemp>::GameDrawer(){}


template <typename FieldDrawerTemp>
void GameDrawer<FieldDrawerTemp>::drawFields(PlayingField userPlayingField, PlayingField enemyPlayingField)
{
    fieldDrawer = FieldDrawerTemp();
    fieldDrawer.printPlayingField(userPlayingField, false);
    fieldDrawer.printPlayingField(enemyPlayingField, true);
}

#endif