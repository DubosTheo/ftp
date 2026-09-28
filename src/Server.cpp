#include "Server.hpp"

#include <iostream>
#include <netinet/in.h>

ftpServer::ftpServer(const std::string strPort)
{
    try {
        _port = std::stoi(strPort);
    } catch (std::invalid_argument &e) {
        throw std::runtime_error("Not a valid port number\n");
    } catch (std::out_of_range &e) {
        throw std::runtime_error("Not a valid port number\n");
    }
    pollfd serverFd{};
    serverFd.fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd.fd == -1)
        throw std::runtime_error("Error creating the socket\n");
    serverFd.events = POLLIN;
    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(_port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverFd.fd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) < 0) {
        close(serverFd.fd);
        throw std::runtime_error("Error binding serverFd\n");
    }
    _fds.push_back(serverFd);
}

void ftpServer::addClient(int fd)
{
    pollfd clientFd{};

    clientFd.fd = fd;
    clientFd.events = POLLIN;
    _fds.push_back(clientFd);
    std::cout << "[+] - New client connected\n";
}

void ftpServer::deleteClient(int fd)
{
    close(fd);
    std::cout << "[-] - A client has disconnected\n";
}


void ftpServer::run()
{
    std::cout << "Server waiting for connection on Port " << _port << std::endl;
    listen(_fds[_serverId].fd, SOMAXCONN);
    while (true) {
        int return_poll = poll(_fds.data(), _fds.size(), -1);
        if (return_poll < 0)
            throw std::runtime_error("Error on poll\n");
        for (size_t i = 0; i < _fds.size(); i++) {
            if (i == _serverId) {
                int clientfd = accept(_fds[_serverId].fd, nullptr, nullptr);
                if (clientfd >= 0)
                    addClient(clientfd);
            }
        }
    }
    close(_fds[_serverId].fd);
}
