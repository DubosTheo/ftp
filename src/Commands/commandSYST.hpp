#pragma once
#include "../ICommand.hpp"

class commandSYST : public ICommand {
public:
    ~commandSYST() override = default;
    commandSYST() = default;
    void execute(Client &client, std::string &command) override;
};
