#include <iostream>
#include <string>
#include "Server.hpp"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 0;
    try {
        if (chdir(argv[2]) < 0)
            throw std::runtime_error("No directory found\n");
        ftpServer server(argv[1]);
        server.run();
    } catch (std::out_of_range &out) {
        std::cerr << out.what();
    } catch (std::exception &e) {
        std::cerr << e.what();
    }
    return 0;
}
