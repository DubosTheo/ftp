#include "commandQUIT.hpp"

#include <unistd.h>

#include "Client.hpp"

void commandQUIT::execute(Client &client, std::string &command, ftpServer &server)
{
    client.setDisconnect(true);
    std::string str = "202 disconnection\r\n";
    client.sendData(str);
}

