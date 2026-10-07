#include "commandTYPE.hpp"

#include "../Client.hpp"

void commandTYPE::execute(Client &client, std::string &command, [[maybe_unused]]ftpServer &server)
{
    if (command == "I")
        return client.sendData("200 Type set to I.\r\n");
    if (command == "A")
        return client.sendData("200 Type set to A.\r\n");
    client.sendData("501 Syntax error\r\n");
}
