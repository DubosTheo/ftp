#pragma once
#include "../ICommand.hpp"

class commandCWD : public ICommand{
public:
    ~commandCWD() override = default;
    commandCWD() = default;
    void execute(Client &client, std::string &command) override;
};
