#include "server.hpp"

Server::Server(const std::string &path) : serverSocket_(path) {
    std::cout << "Server UNIX socket bound to " << path << std::endl;
}

void Server::start()
{
    std::cout << "Server running!" << std::endl;

    while (true) {
        try {
            ClientSocket client = serverSocket_.acceptClient();
            std::cout << "New connection!" << std::endl;
            client.processMessages();
            std::cout << "Client disconnected!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error while working with client: " << e.what() << std::endl;
        }
    }
}
