#include "commandSYST.hpp"

#include "../Client.hpp"

void commandSYST::execute(Client &client, [[maybe_unused]]std::string &command, [[maybe_unused]]ftpServer &server)
{
    std::string str = "215 UNIX Type: L8\r\n";
    client.sendData(str);
}
