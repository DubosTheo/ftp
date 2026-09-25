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
    auto serverFd = std::make_unique<pollfd>();
    if (!serverFd)
        throw std::runtime_error("Can't create serverfd\n");
    serverFd->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd->fd == -1)
        throw std::runtime_error("Error creating the socket\n");
    serverFd->events = POLLIN;
    sockaddr_in servAddr{};
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(_port);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serverFd->fd, reinterpret_cast<sockaddr*>(&servAddr), sizeof(servAddr)) < 0) {
        close(serverFd->fd);
        throw std::runtime_error("Error binding serverFd\n");
    }
    _fds.push_back(std::move(serverFd));
}

void ftpServer::run() const
{
    while (true) {
        listen(_fds[_serverId]->fd, 5);
        std::cout << "Server waiting for connection on Port " << _port << std::endl;
        int clientfd = accept(_fds[_serverId]->fd, nullptr, nullptr);
        if (clientfd >= 0) {
            std::string Message = "Hello client!\n";
            write(clientfd, Message.c_str(), Message.size());
            char buffer[1024] = {0};
            ssize_t bytesRead = read(clientfd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                std::cout << "Reçu du client : " << buffer << "\n";
            }
            close(clientfd);
        }
    }
    close(_fds[_serverId]->fd);
}

