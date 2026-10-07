#include "commandPORT.hpp"

#include <vector>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Client.hpp"

void commandPORT::execute(Client &client, std::string &command)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }

    std::vector<int> info;
    std::stringstream ss(command);
    std::string number;

    while (std::getline(ss, number, ',')) {
        try {
            info.push_back(std::stoi(number));
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            std::string err = "502 invalid port\r\n";
            client.sendData(err);
            return;
        }
    }
    if (info.size() != 6) {
        client.sendData("502 not enough number for assign port\r\n");
        return;
    }
    std::string ip = std::to_string(info[0]) + '.' + std::to_string(info[1]) + '.'
    + std::to_string(info[2]) + '.' + std::to_string(info[3]);

    int port = (info[4] * 256) + info[5];
    client.closeDataFd();
    int dataFd = socket(AF_INET, SOCK_STREAM, 0);
    if (dataFd < 0) {
        client.sendData("425 error creating the socket\r\n");
        return;
    }
    struct sockaddr_in addr{};
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) < 0) {
        close(dataFd);
        client.sendData("502 can't convert to ip network\r\n");
        return;
    }
    if (connect(dataFd, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) < 0) {
        client.sendData("425 can't open connection\r\n");
        close(dataFd);
        return;
    }
    client.setDataFd(dataFd);
    client.sendData("200 port correctly assigned\r\n");
}
