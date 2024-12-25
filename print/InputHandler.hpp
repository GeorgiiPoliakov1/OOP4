#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H
#include "CommandHandler.h"
#include <iostream>
#include <vector>
#include "../play/Game.h"
#include "GameMessage.h"

template <typename CommandHandlerTemp>
class InputHandler
{
  public:
   InputHandler();
   Command enterCommand();
   std::pair<int, int> readCoords();
   std::pair<int, int> getAttackCoordinates();
   std::pair<int, int> getAbilityCoordinates();
   Layout readShipLayout();
   std::pair<Layout, std::pair<size_t, size_t>> readShipFromUser(int shipSize);
  private:
   CommandHandlerTemp commandHandler;
   GameMessage gameMessage;
   
};

template <typename CommandHandlerTemp>
InputHandler<CommandHandlerTemp>::InputHandler() : commandHandler(CommandHandlerTemp("settings.txt")) {}

template <typename CommandHandlerTemp>
Command InputHandler<CommandHandlerTemp>::enterCommand() 
{
    std::cout << commandHandler.allCommands() << std::endl;
    Command command;
    char choice;
    std::cin >> choice;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Error: Invalid input" << std::endl;
    }
    try{
        command = this->commandHandler.getCommand(choice);
    }catch(std::invalid_argument& e){
        std::cerr << "There is no such a command!" << std::endl;
    }
    return command;
}

template <typename CommandHandlerTemp>
std::pair<int, int> InputHandler<CommandHandlerTemp>::getAttackCoordinates() 
{
   std::cout << "Enter x, y coordinates for attack: ";
   return readCoords();
}

template <typename CommandHandlerTemp>
std::pair<int, int> InputHandler<CommandHandlerTemp>::getAbilityCoordinates() 
{
   gameMessage.messageForAbilityUse();
   return readCoords();
}

template <typename CommandHandlerTemp>
std::pair<int, int> InputHandler<CommandHandlerTemp>::readCoords() 
{
    int x, y;
    std::cin >> x >> y;
    return std::pair<size_t, size_t>{x, y};
}

template <typename CommandHandlerTemp>
 std::pair<Layout, std::pair<size_t, size_t>> InputHandler<CommandHandlerTemp>::readShipFromUser(int shipSize) 
 {
    gameMessage.messageForShipPlacement(shipSize);
    Layout layoutInput = readShipLayout();
    gameMessage.messageForEnteringCoords();
    std::pair<size_t, size_t> coords = readCoords();
    return std::pair<Layout, std::pair<size_t, size_t>>{layoutInput, coords};

}

template <typename CommandHandlerTemp>
Layout InputHandler<CommandHandlerTemp>::readShipLayout() 
{
    int layoutInput;
    while (true) {
        std::cin >> layoutInput;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Error: Invalid input. Please enter 0 or 1." << std::endl;
            continue;
        }
        if (layoutInput == 0) {
            return Layout::HORIZONTAL;
        } else if (layoutInput == 1) {
            return Layout::VERTICAL;
        } else {
            std::cerr << "Error: Invalid Layout. Please enter 0 or 1." << std::endl;
        }
    }
}

#endif