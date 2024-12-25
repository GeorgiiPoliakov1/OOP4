#include "CommandHandler.h"

CommandHandler::CommandHandler(const std::string &filePath)
{   if (loadFile(filePath)){
        return;
    }
    commandsToUse['s'] = SHOOT;
    commandsToUse['a'] = ABILITY;
    commandsToUse['l'] = LOAD;
    commandsToUse['v'] = SAVEGAME; 
    commandsToUse['q'] = QUIT;
    commandsToUse['n'] = NEWGAME;
}

bool CommandHandler::loadFile(const std::string &filePath)
{
    std::map<char, Command> keysAndCommands;
    std::string line;
    std::ifstream file(filePath);
    if (!file.is_open()){
        std::cerr << "Couldn`t open the file" << std::endl;
        return false;
    }
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char key;
        std::string commandName;
        if (!(iss >> key >> commandName)) {
            std::cerr << "Wrong file format" << line << std::endl;
            return false;
        }
        Command command;
        if (commandName == "shoot") {
            command = Command::SHOOT;
        } else if (commandName == "ability") {
            command = Command::ABILITY;
        } else if (commandName == "save") {
            command = Command::SAVEGAME;
        } else if (commandName == "load") {
            command = Command::LOAD;
        } else if (commandName == "quit") {
            command = Command::QUIT;
        }else if (commandName == "newGame"){
            command = Command::NEWGAME;
        }else {
            std::cerr << "Unknown command! " << commandName << std::endl;
            return false;
        }
        if (keysAndCommands.find(key) != keysAndCommands.end()) {
            std::cerr << "One assignment key for two different commands. Key that you used twice: " << key << std::endl;
            return false;
        }
        for (const auto& pair : keysAndCommands) {
            if (pair.second == command) {
                std::cerr << "Two assingment key for one command" << std::endl;
                return false;
            }
        }
        keysAndCommands[key] = command;
    }
    commandsToUse = std::move(keysAndCommands);
    return true;
}

std::string CommandHandler::turnCommandToString(Command command)
{
    switch (command) {
        case SHOOT:
            return "shoot";
        case ABILITY:
            return "ability";
        case SAVEGAME:
            return "save";
        case QUIT:
            return "quit";
        case LOAD:
            return "load";
        case NEWGAME:
            return "start new game";
        default:
            throw std::invalid_argument("Invalid command");
    }
}
std::string CommandHandler::allCommands() 
{
    std::stringstream strstream;
    strstream << "Enter command from list:" << std::endl;
    for (auto const& command : commandsToUse) {
        strstream << command.first << " - " << this->turnCommandToString(command.second) << std::endl;
    }
    return strstream.str();
}

Command CommandHandler::getCommand(char value)
{
    if (commandsToUse.find(value) == commandsToUse.end()){
        throw std::invalid_argument("Invalid key");
    }
    return commandsToUse[value];
}