#pragma once
#include "../ICommand.hpp"

class commandPASV : public ICommand {
public:
    ~commandPASV() override = default;
    commandPASV() = default;
    void execute(Client &client, std::string &command) override;
};
