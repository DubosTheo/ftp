#include "commandSTRU.hpp"
#include "../Client.hpp"

void commandSTRU::execute(Client &client, std::string &command, [[maybe_unused]]ftpServer &server)
{
    if (command.empty())
        return client.sendData("501 Syntax error\r\n");
    for (char &c : command)
        c = static_cast<char>(std::toupper(c));
    if (command == "F")
        return client.sendData("200 Type set to F.\r\n");
    if (command == "R")
        return client.sendData("200 Type set to R.\r\n");
    if (command == "P")
        return client.sendData("200 Type set to P.\r\n");
    client.sendData("501 Syntax error\r\n");
}
