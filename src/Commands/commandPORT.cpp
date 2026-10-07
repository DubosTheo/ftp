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
    client.setActivePort(port);
    client.setActiveIp(ip);
    client.sendData("200 port correctly assigned\r\n");
}
