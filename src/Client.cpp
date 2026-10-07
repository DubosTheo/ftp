#include "Client.hpp"

#include <ctime>
#include <stdexcept>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <sstream>

Client::Client(int fd) : _fd(fd), _dataFd(-1)
{
}

void Client::closeDataFd()
{
    if (_dataFd != -1) {
        close(_dataFd);
        _dataFd = -1;
    }
}

Client::~Client()
{
    closeDataFd();
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
