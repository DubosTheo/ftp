#include "commandMODE.hpp"
#include "../Client.hpp"

void commandMODE::execute(Client &client, std::string &command, [[maybe_unused]]ftpServer &server)
{
    if (command.empty())
        return client.sendData("501 Syntax error\r\n");
    for (char &c : command)
        c = static_cast<char>(std::toupper(c));
    if (command == "S")
        return client.sendData("200 Type set to S.\r\n");
    if (command == "B")
        return client.sendData("200 Type set to B.\r\n");
    if (command == "C")
        return client.sendData("200 Type set to C.\r\n");
    client.sendData("501 Syntax error\r\n");
}
