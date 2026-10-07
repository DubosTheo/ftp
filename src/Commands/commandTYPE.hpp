#pragma once
#include "../ICommand.hpp"

class commandTYPE : public ICommand {
public:
    void execute(Client &client, std::string &command) override;
    ~commandTYPE() override = default;
    commandTYPE() = default;
};
