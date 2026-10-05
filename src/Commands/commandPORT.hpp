#pragma once
#include "../ICommand.hpp"

class commandPORT : public ICommand {
public:
    ~commandPORT() override = default;
    commandPORT() = default;
    void execute(Client &client, std::string &command, ftpServer &server) override;
};
