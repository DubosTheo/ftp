#include "commandQUIT.hpp"

#include <unistd.h>

#include "Client.hpp"

void commandQUIT::execute(Client &client, std::string &command, ftpServer &server)
{
    (void)server;
    (void)command;
    client.setDisconnect(true);
    std::string str = "220 disconnection\r\n";
    client.sendData(str);
}

