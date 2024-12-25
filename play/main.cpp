#include "../print/GameHandler.hpp"
#include "../print/InputHandler.hpp"
#include "../print/GameDrawer.hpp"
#include "../print/FieldDrawer.h"
#include "../print/CommandHandler.h"
#include "Game.h"

int main(){
    Game* game = new Game();
    GameHandler<InputHandler<CommandHandler>> gameHandler(game);
}