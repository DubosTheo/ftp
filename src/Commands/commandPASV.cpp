#include "commandPASV.hpp"

#include <stdexcept>
#include <unistd.h>
#include <c++/13/ctime>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Client.hpp"

void commandPASV::execute(Client &client, [[maybe_unused]]std::string &command)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }

    int tmpFd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;
    if (bind(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) {
        close(tmpFd);
        return client.sendData("502 Can't bind fd\r\n");
    }
    listen(tmpFd, 1);
    socklen_t len = sizeof(addr);
    if (getsockname(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), &len) < 0) {
        close(tmpFd);
        return client.sendData("405 Can't get sockname\r\n");
    }
    int port = ntohs(addr.sin_port);
    int p1 = port / 256;
    int p2 = port % 256;
    std::string resp = "227 Entering Passive Mode (127,0,0,1," + std::to_string(p1) + "," + std::to_string(p2) + ").\r\n";
    client.sendData(resp);
    client.setPasv(tmpFd);
}
