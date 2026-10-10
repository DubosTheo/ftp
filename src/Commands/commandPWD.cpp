#include "commandPWD.hpp"
#include <filesystem>
#include <iostream>

#include "../Client.hpp"

void commandPWD::execute(Client &client, [[maybe_unused]]std::string &command)
{
    client.sendData("257 \""  + client.getCurrentPath().generic_string() + "\" is current directory\r\n");
}
