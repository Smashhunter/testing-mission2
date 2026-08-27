#include "server.hpp"

int main() {
    try {
        Server server(SOCKET_PATH);
        server.start();
    } catch (const std::exception& e) {
        std::cerr << "Fatal server error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
