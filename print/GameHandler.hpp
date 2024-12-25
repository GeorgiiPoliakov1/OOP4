#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H
#include "../play/Game.h"
#include "CommandHandler.h"
#include "GameMessage.h"
#include <vector>
#include <stdexcept>


template<typename InputHandler>
class GameHandler
{
 public:
    GameHandler(Game* game);
    ~GameHandler() {delete game;};
    void startNewGame();
    void play();
    void makeMove();

 private:
    Game* game;
    InputHandler inputHandler;
    GameMessage gameMessage;
};

template<typename InputHandler>
GameHandler<InputHandler>::GameHandler(Game* game) : game(game), inputHandler(InputHandler())
{
    this->play();
}

template<typename InputHandler>
void GameHandler<InputHandler>::startNewGame() 
{
    gameMessage.messageWelcome();
    game->arrangeUserShips();
    game->arrangeEnemyShips();
    this->play();
}

template<typename InputHandler>
void GameHandler<InputHandler>::play() 
{
    GameMessage gameMessage;
    while(true){
        this->makeMove();
        if (game->getGameStatus() == WIN){
            gameMessage.messageForGameEnd(true);
            game->arrangeEnemyShips();
        }
        else if (game->getGameStatus() == LOSS){
            gameMessage.messageForGameEnd(false);
            this->startNewGame();
        }
    }
}


template<typename InputHandler>
void GameHandler<InputHandler>::makeMove()
{
    Command userCommand = this->inputHandler.enterCommand();
    if (userCommand == SHOOT){
        if (game->getGameStatus() != NOT_STARTED){
            pair<int, int> coordAttack = inputHandler.getAttackCoordinates();
            game->makeUserMove(coordAttack.first, coordAttack.second);
        }else{
            std::cerr << "Your game is not started" << std::endl;
        }
    }else if (userCommand == ABILITY){
        if (game->getGameStatus() != NOT_STARTED){
            pair<int, int> coordAbil = inputHandler.getAbilityCoordinates();
            if (game->applyAbility(coordAbil.first, coordAbil.second) == false){
                pair<int, int> coordAttack = inputHandler.getAttackCoordinates();
                game->makeUserMove(coordAttack.first, coordAttack.second);
            }
        }else{
            std::cerr << "Your game is not started" << std::endl;
        }
    }else if (userCommand == NEWGAME){
        this->startNewGame();
    }else if (userCommand == SAVEGAME){
        game->saveGame();
    }else if (userCommand == LOAD){
        game->loadGame();
    }else if (userCommand == QUIT){
        exit(0);
    }
    
}
#endif