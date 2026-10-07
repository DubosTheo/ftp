#include "commandFEAT.hpp"

#include "../Client.hpp"

void commandFEAT::execute(Client &client, [[maybe_unused]]std::string &command)
{
    std::string str = "211-Features:\r\n211 End\r\n";
    client.sendData(str);
}
