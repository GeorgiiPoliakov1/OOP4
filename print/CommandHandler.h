#ifndef COMMAND_HANDLER
#define COMMAND_HANDLER
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
enum Command{
    SHOOT,
    ABILITY,
    SAVEGAME,
    LOAD,
    QUIT,
    NEWGAME
};

class CommandHandler
{
private:
    std::map<char, Command> commandsToUse;

public:
    CommandHandler(const std::string &filePath);
    Command getCommand(char value);
    bool loadFile(const std::string& filePath);
    std::string turnCommandToString(Command command);
    std::string allCommands();
};
#endif