#include "commandUSER.hpp"

#include "Client.hpp"

void commandUSER::execute(Client &client, std::string &command)
{
    client.setUsername(command);
    std::string str = "331 username set!\r\n";
    client.sendData(str);
}
