#include "Quit.hpp"

#include "Client.hpp"

void Quit::execute(Client &client, std::string &command, ftpServer &server)
{
    client.setDisconnect(true);
}

