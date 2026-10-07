#include "commandManager.hpp"
#include "Commands/commandQUIT.hpp"
#include <sstream>
#include "Client.hpp"
#include "Commands/commandPASS.hpp"
#include "Commands/commandSYST.hpp"
#include "Commands/commandUSER.hpp"
#include "Commands/commandFEAT.hpp"
#include "Commands/commandPASV.hpp"
#include "Commands/commandRETR.hpp"
#include "Commands/commandPORT.hpp"
#include "Commands/commandTYPE.hpp"

commandManager::commandManager()
{
    _commands["QUIT"] = std::make_unique<commandQUIT>();
    _commands["USER"] = std::make_unique<commandUSER>();
    _commands["PASS"] = std::make_unique<commandPASS>();
    _commands["SYST"] = std::make_unique<commandSYST>();
    _commands["FEAT"] = std::make_unique<commandFEAT>();
    _commands["RETR"] = std::make_unique<commandRETR>();
    _commands["PASV"] = std::make_unique<commandPASV>();
    _commands["PORT"] = std::make_unique<commandPORT>();
    _commands["TYPE"] = std::make_unique<commandTYPE>();
}

void commandManager::execute(Client &client, const std::string &command, ftpServer &server)
{
    std::stringstream ss(command);
    std::string cmdName;
    std::string args;

    ss >> cmdName;
    for (char &c : cmdName)
        c = static_cast<char>(std::toupper(c));
    std::getline(ss >> std::ws, args);
    auto it = _commands.find(cmdName);
    if (it != _commands.end())
        return it->second->execute(client, args, server);
    std::string err = "502 Command not found or not logged in\r\n";
    client.sendData(err);
}
