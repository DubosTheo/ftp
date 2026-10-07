#include "Client.hpp"

#include <ctime>
#include <stdexcept>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Client::Client(int fd) : _fd(fd), _pasvFd(-1), _activePort(0)
{
}

int Client::handleDataFd()
{
    int dataFd = -1;

    if (_pasvFd >= 0) {
        dataFd = accept(_pasvFd, nullptr, nullptr);
        close(_pasvFd);
        _pasvFd = -1;
        if (dataFd < 0) {
            sendData("502 Error creating the connection\r\n");
            return -1;
        }
    } else if (_activePort > 0) {
        int port = _activePort;
        _activePort = 0;
        dataFd = socket(AF_INET, SOCK_STREAM, 0);
        if (dataFd < 0) {
            sendData("425 error creating the socket\r\n");
            return -1;
        }
        struct sockaddr_in addr{};
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        if (inet_pton(AF_INET, _activeIp.c_str(), &addr.sin_addr) < 0) {
            close(dataFd);
            sendData("502 can't convert to ip network\r\n");
            return -1;
        }
        if (connect(dataFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) {
            sendData("425 can't open connection\r\n");
            close(dataFd);
            return -1;
        }
    }
    return dataFd;
}

void Client::appendBuffer(std::string buffer)
{
    _buffer += buffer;
}

size_t Client::readData()
{
    std::vector<char> buffer(1024);
    ssize_t size = 0;

    size = read(_fd, buffer.data(), buffer.size());
    if (size == 0)
        return size;
    if (size < 0)
        throw std::runtime_error("Can't read client\n");
    const std::string tmp = buffer.data();
    appendBuffer(tmp);
    return size;
}

bool Client::reformatCommand(std::string &command)
{
    std::string partCommand = _buffer;
    size_t pos = partCommand.find("\r\n");

    if (pos == std::string::npos)
        return false;
    command = partCommand.substr(0, pos);
    _buffer.erase(0, pos + 2);
    return true;
}

void Client::sendData(const std::string& str) const
{
    if (write(_fd, str.c_str(), str.size()) < 0)
        throw std::runtime_error("Can't write on client fd\n");
}
