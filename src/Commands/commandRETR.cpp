#include "commandRETR.hpp"

#include <unistd.h>
#include <sys/wait.h>
#include "Client.hpp"
#include <fstream>

void commandRETR::execute(Client &client, std::string &command, [[maybe_unused]]ftpServer &server)
{
    if (!client.getLoggedIn()) {
        client.sendData("530 Please loggin\r\n");
        return;
    }
    if (command.empty()) {
        std::string err = "501 error arguments\r\n";
        client.sendData(err);
        return;
    }
    int dataFd = client.getDataFd();
    if (dataFd < 0) {
        client.sendData("425 Use PORT or PASV first.\r\n");
        return;
    }

    std::ifstream file(command, std::ios::binary);
    if (!file.is_open()) {
        client.sendData("550 Failed to open file.\r\n");
        return;
    }
    client.sendData("150 Opening BINARY mode data connection.\r\n");

    pid_t pid = fork();
    if (pid < 0) {
        client.sendData("451 Local error in processing.\r\n");
        file.close();
        return;
    }
    if (pid == 0) {
        char buffer[4096];
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
            ssize_t bytesToWrite = file.gcount();
            ssize_t bytesWritten = 0;
            while (bytesWritten < bytesToWrite) {
                ssize_t ret = write(dataFd, buffer + bytesWritten, bytesToWrite - bytesWritten);
                if (ret <= 0) {
                    file.close();
                    close(dataFd);
                    exit(1);
                }
                bytesWritten += ret;
            }
        }
        file.close();
        close(dataFd);
        exit(0);
    }
    file.close();
    client.closeDataFd();

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        client.sendData("226 Transfer complete.\r\n");
    } else {
        client.sendData("451 Failure writing to local file/stream.\r\n");
    }
}
