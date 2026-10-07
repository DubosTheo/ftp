#pragma once
#include <vector>
#include <memory>
#include <poll.h>
#include "Client.hpp"
#include <map>
#include "commandManager.hpp"

class ftpServer {
private:
    std::vector<pollfd> _fds;
    commandManager _commandManager;
    std::map<int, Client> _clients;
    size_t _serverId = 0;
    int _port;
public:
    explicit ftpServer(std::string strPort);
    void run();
    void addClient(int fd);
    void deleteClient(int i, int fd);
    bool listenClient(Client &client);
};
