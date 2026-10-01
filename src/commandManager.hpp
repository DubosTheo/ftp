#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "ICommand.hpp"

class commandManager {
    std::unordered_map<std::string, std::unique_ptr<ICommand>> _commands;
public:
    commandManager();
    void execute(Client &client, const std::string &command, ftpServer &server);
};
