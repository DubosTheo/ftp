#pragma once
#include <string>

class ftpServer;
class Client;

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute(Client &client, std::string &command) = 0;
};
