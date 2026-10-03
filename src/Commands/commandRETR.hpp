#pragma once
#include "../ICommand.hpp"

class  commandRETR : public ICommand {
public:
    ~commandRETR() override = default;
    commandRETR() = default;
    void execute(Client &client, std::string &command, ftpServer &server) override;
};
