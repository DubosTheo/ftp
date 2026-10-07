#include "commandEPSV.hpp"
#include "../Client.hpp"
#include <stdexcept>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

void commandEPSV::execute(Client &client, [[maybe_unused]]std::string &command)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }

    int tmpFd = socket(AF_INET6, SOCK_STREAM, 0);

    if (tmpFd < 0) {
        tmpFd = socket(AF_INET, SOCK_STREAM, 0);
        if (tmpFd < 0)
            return client.sendData("425 Can't create socket\r\n");
    }
    int sock = 0;
    setsockopt(tmpFd, IPPROTO_IPV6, IPV6_V6ONLY, &sock, sizeof(sock));
    struct sockaddr_in6 addr{};
    addr.sin6_family = AF_INET6;
    addr.sin6_addr = in6addr_any;
    addr.sin6_port = 0;
    if (bind(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) {
        close(tmpFd);
        return client.sendData("425 Can't bind fd\r\n");
    }
    if (listen(tmpFd, 1) < 0) {
        close(tmpFd);
        client.sendData("425 Can't listen on socket.\r\n");
        return;
    }
    socklen_t len = sizeof(addr);
    if (getsockname(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), &len) < 0) {
        close(tmpFd);
        return client.sendData("405 Can't get sockname\r\n");
    }
    int port = ntohs(addr.sin6_port);
    std::string resp = "229 Entering Extended Passive Mode (|||" + std::to_string(port) + "|)\r\n";
    client.sendData(resp);
    client.setPasv(tmpFd);
}
