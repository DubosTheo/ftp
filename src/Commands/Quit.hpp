#include <string>
#include "../ICommand.hpp"

class Client;
class ftpServer;

class Quit : public ICommand {
public:
    ~Quit() override = default;
    Quit() = default;
    void execute(Client &client, std::string &command, ftpServer &server) override;
};
