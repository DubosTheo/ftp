#include "commandManager.hpp"
#include "Commands/Quit.hpp"
#include <sstream>
#include "Client.hpp"

commandManager::commandManager()
{
    _commands["QUIT"] = std::make_unique<Quit>();
}

void commandManager::execute(Client &client, const std::string &command, ftpServer &server)
{
    std::stringstream ss(command);
    std::string cmdName;
    std::string args;

    ss >> cmdName;
    for (char &c : cmdName) {
        c = static_cast<char>(std::toupper(c));
    }
    std::getline(ss >> std::ws, args);
    auto it = _commands.find(cmdName);
    if (it != _commands.end())
        it->second->execute(client, args, server);
    else {
        std::string err = "502 Command not found\r\n";
        client.sendData(err);
    }
}
