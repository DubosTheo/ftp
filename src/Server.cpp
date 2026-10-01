#include "Server.hpp"
#include "Client.hpp"
#include <iostream>
#include <netinet/in.h>
#include <sstream>

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
    std::string str = "220 - Hello client!\r\n";
    _clients.insert({fd, Client(fd)});
    write(fd, str.c_str(), str.size());
}

void ftpServer::deleteClient(int i, const int fd)
{
    close(_fds[i].fd);
    _fds.erase(_fds.begin() + i);
    _clients.erase(fd);
    std::cout << "[-] - A client has disconnected\n";
}

void ftpServer::parseCommand(std::string &command, Client &client)
{
    std::stringstream ss;
    std::string tmpCommand;

    ss >> tmpCommand;
}


bool ftpServer::listenClient(Client &client)
{
    if (client.needToDisconnect())
        return false;
    size_t size = client.readData();
    if (size == 0)
        return true;
    std::string command;
    while (client.reformatCommand(command))
        _commandManager.execute(client, command, *this);
    return true;
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
            if (!(_fds[i].revents & POLLIN))
                continue;
            if (i == _serverId) {
                int clientfd = accept(_fds[_serverId].fd, nullptr, nullptr);
                if (clientfd >= 0)
                    addClient(clientfd);
                continue;
            }
            if (!listenClient(_clients.at(_fds[i].fd))) {
                deleteClient(i, _fds[i].fd);
                i--;
            }
        }
    }
    close(_fds[_serverId].fd);
}
