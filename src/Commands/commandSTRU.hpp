#pragma once
#include "../ICommand.hpp"

class commandSTRU : public ICommand{
public:
    void execute(Client &client, std::string &command, ftpServer &server) override;
    ~commandSTRU() override = default;
    commandSTRU() = default;
};
