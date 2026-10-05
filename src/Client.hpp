#pragma once
#include <string>

class ftpServer;

class Client {
    int _fd;
    int _dataFd;
    std::string _password;
    std::string _username;
    std::string _buffer;
    bool _isAuth = false;
    bool _needToDisconnect = false;
public:
    explicit Client(int fd);
    void appendBuffer(std::string buffer);
    size_t readData();
    void sendData(const std::string& str) const;
    [[nodiscard]] int getFd() const {return _fd;}
    bool reformatCommand(std::string &command);
    [[nodiscard]] bool needToDisconnect() const {return _needToDisconnect;}
    void setDisconnect(bool disconnect) { _needToDisconnect = disconnect;}
    void setUsername(const std::string &username) {_username = username;}
    void setPassword(const std::string &password) {_password = password;}
    void setDataFd(int dataFd) {_dataFd = dataFd;}
    [[nodiscard]] int getDataFd() const {return _dataFd;}
    void closeDataFd();
};
