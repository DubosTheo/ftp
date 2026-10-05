#pragma once
#include "../ICommand.hpp"

class commandPASV : public ICommand {
public:
    void execute(Client &client, std::string &command, ftpServer &server) override;
};
