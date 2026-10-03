#include "commandManager.hpp"
#include "Commands/commandQUIT.hpp"
#include <sstream>
#include "Client.hpp"
#include "Commands/commandPASS.hpp"
#include "Commands/commandUSER.hpp"

commandManager::commandManager()
{
    _commands["QUIT"] = std::make_unique<commandQUIT>();
    _commands["USER"] = std::make_unique<commandUSER>();
    _commands["PASS"] = std::make_unique<commandPASS>();
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
        return it->second->execute(client, args, server);
    std::string err = "502 Command not found\r\n";
    client.sendData(err);
}
