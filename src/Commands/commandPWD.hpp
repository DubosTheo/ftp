#pragma once

#include "../ICommand.hpp"

class commandPWD : public ICommand {
public:
    void execute(Client &client, std::string &command) override;
    ~commandPWD() override = default;
    commandPWD() = default;
};
