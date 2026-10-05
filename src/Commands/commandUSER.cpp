#include "commandUSER.hpp"

#include "Client.hpp"

void commandUSER::execute(Client &client, std::string &command, [[maybe_unused]]ftpServer &server)
{
    client.setUsername(command);
    std::string str = "331 username set!\r\n";
    client.sendData(str);
}
