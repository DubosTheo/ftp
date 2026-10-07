#pragma once
#include <string>
#include "../ICommand.hpp"

class Client;
class ftpServer;

class commandQUIT : public ICommand {
public:
    ~commandQUIT() override = default;
    commandQUIT() = default;
    void execute(Client &client, std::string &command) override;
};
