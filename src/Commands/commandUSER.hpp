#pragma once

#include "ICommand.hpp"

class commandUSER : public ICommand{
public:
    ~commandUSER() override = default;
    commandUSER() = default;
    void execute(Client &client, std::string &command) override;
};
