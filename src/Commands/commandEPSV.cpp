#include "commandEPSV.hpp"
#include "../Client.hpp"
#include <stdexcept>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void commandEPSV::execute(Client &client, std::string &command)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }

    int tmpFd = socket(AF_INET, SOCK_STREAM, 0);

    if (tmpFd < 0)
        return client.sendData("425 Can't create socket\r\n");
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;
    if (bind(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) {
        close(tmpFd);
        return client.sendData("425 Can't bind fd\r\n");
    }
    listen(tmpFd, 1);
    socklen_t len = sizeof(addr);
    if (getsockname(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), &len) < 0) {
        close(tmpFd);
        return client.sendData("405 Can't get sockname\r\n");
    }
    int port = ntohs(addr.sin_port);
    std::string resp = "229 Entering Extended Passive Mode (|||" + std::to_string(port) + "|)\r\n";
    client.sendData(resp);
    client.setPasv(tmpFd);
}
