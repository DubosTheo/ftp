#include "commandFEAT.hpp"

#include "../Client.hpp"

void commandFEAT::execute(Client &client, std::string &command, ftpServer &server)
{
    (void)command;
    (void)server;
    std::string str = "211-Features:\r\n211 End\r\n";
    client.sendData(str);
}
