#pragma once
#include "../ICommand.hpp"

class commandPASS : ICommand{
public:
    ~commandPASS() override = default;
    commandPASS() = default;
    void execute(Client &client, std::string &command, ftpServer &server) override;
};
