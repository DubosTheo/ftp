#pragma once
#include "../ICommand.hpp"

class commandMODE : public ICommand{
public:
    void execute(Client &client, std::string &command) override;
    ~commandMODE() override = default;
    commandMODE() = default;
};
