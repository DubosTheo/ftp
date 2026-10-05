#include "commandPASV.hpp"

#include <stdexcept>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "Client.hpp"

void commandPASV::execute(Client &client, [[maybe_unused]]std::string &command, [[maybe_unused]]ftpServer &server)
{
    int tmpFd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 0;
    if (bind(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0)
        throw std::runtime_error("Can't bind dataFd\n");
    listen(tmpFd, 1);
    socklen_t len = sizeof(addr);
    getsockname(tmpFd, reinterpret_cast<struct sockaddr *>(&addr), &len);
    int port = ntohs(addr.sin_port);
    int p1 = port / 256;
    int p2 = port % 256;
    std::string resp = "227 Entering Passive Mode (127,0,0,1," + std::to_string(p1) + "," + std::to_string(p2) + ").\r\n";
    client.sendData(resp);

    int dataFd = accept(tmpFd, nullptr, nullptr);
    close(tmpFd);
    client.setDataFd(dataFd);
}
