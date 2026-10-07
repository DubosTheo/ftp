#pragma once
#include "../ICommand.hpp"

class commandPASS : public ICommand{
public:
    ~commandPASS() override = default;
    commandPASS() = default;
    void execute(Client &client, std::string &command) override;
};
