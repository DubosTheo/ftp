#pragma once
#include "../ICommand.hpp"

class commandEPSV : public ICommand {
public:
    void execute(Client &client, std::string &command) override;
    ~commandEPSV() override = default;
    commandEPSV() = default;
};
