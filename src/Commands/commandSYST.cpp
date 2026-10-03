#include "commandSYST.hpp"

#include "../Client.hpp"

void commandSYST::execute(Client &client, std::string &command, ftpServer &server)
{
    (void)server;
    (void)command;
    std::string str = "215 UNIX Type: L8\r\n";
    client.sendData(str);
}
