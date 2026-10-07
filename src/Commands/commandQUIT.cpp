#include "commandQUIT.hpp"

#include <unistd.h>

#include "Client.hpp"

void commandQUIT::execute(Client &client, [[maybe_unused]]std::string &command, [[maybe_unused]]ftpServer &server)
{
    client.setDisconnect(true);
    std::string str = "221 disconnection\r\n";
    client.sendData(str);
}

