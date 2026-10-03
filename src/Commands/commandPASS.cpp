#include "commandPASS.hpp"

#include <unistd.h>

#include "Client.hpp"

void commandPASS::execute(Client &client, std::string &command, ftpServer &server)
{
    (void)server;
    (void)command;
    client.setPassword(command);
    std::string str = "202 password set!\r\n";
    client.sendData(str);
}
