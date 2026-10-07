#include "commandPWD.hpp"
#include <filesystem>
#include <iostream>

#include "../Client.hpp"

void commandPWD::execute(Client &client, std::string &command)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }

    try {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::string cwdStr = cwd.string();
        client.sendData("257 \""  + cwdStr + "\" is current directory\r\n");
    } catch (const std::filesystem::filesystem_error &e) {
        client.sendData("550 error path\r\n");
    }
}
