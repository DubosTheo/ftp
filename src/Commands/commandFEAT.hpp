#pragma once
#include "../ICommand.hpp"

class commandFEAT : public ICommand{
public:
    ~commandFEAT() override = default;
    commandFEAT() = default;
    void execute(Client &client, std::string &command) override;
};
