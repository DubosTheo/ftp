#pragma once
#include <vector>
#include <memory>
#include <poll.h>

class ftpServer {
private:
    std::vector<pollfd> _fds;
    size_t _serverId = 0;
    int _port;
public:
    explicit ftpServer(std::string strPort);
    void run();
    void addClient(int fd);
    static void deleteClient(int fd);
};
