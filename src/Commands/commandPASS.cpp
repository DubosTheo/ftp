#include "commandPASS.hpp"

#include <unistd.h>

#include "Client.hpp"

void commandPASS::execute(Client &client, std::string &command)
{
    if (client.getUsername() != "anonymous") {
        client.sendData("530 Please loggin\r\n");
        return;
    }
    client.setDisconnect(false);
    client.setLoggedIn(true);
    client.setPassword(command);
    std::string str = "202 password set!\r\n";
    client.sendData(str);
}
