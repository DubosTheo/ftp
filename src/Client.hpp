#pragma once
#include <string>

class ftpServer;

class Client {
    int _fd;
    int _pasvFd;
    int _activePort;
    std::string _password;
    std::string _username;
    std::string _buffer;
    std::string _activeIp;
    bool _isAuth = false;
    bool _needToDisconnect = false;
    bool _isLoggedIn = false;
public:
    explicit Client(int fd);
    void appendBuffer(std::string buffer);
    size_t readData();
    int handleDataFd();
    void sendData(const std::string& str) const;
    [[nodiscard]] int getFd() const {return _fd;}
    bool reformatCommand(std::string &command);
    [[nodiscard]] bool needToDisconnect() const {return _needToDisconnect;}
    void setDisconnect(bool disconnect) { _needToDisconnect = disconnect;}
    void setUsername(const std::string &username) {_username = username;}
    void setPassword(const std::string &password) {_password = password;}
    void setLoggedIn(bool isLogged) {_isLoggedIn = isLogged;}
    [[nodiscard]] bool getLoggedIn() const {return _isLoggedIn;}
    std::string getUsername() {return _username;}
    [[nodiscard]] int getPasv() const {return _pasvFd;}
    void setPasv(const int pasv) {_pasvFd = pasv;};
    void setActivePort(int activePort) {_activePort = activePort;}
    [[nodiscard]] int getActivePort() const {return _activePort;}
    void setActiveIp(const std::string &activeIp) {_activeIp = activeIp;}
    std::string getActiveIp() {return _activeIp;}
};
