#include "app.hpp"
#include <iostream>

int main() {
    try {
        App app(SERVER_SOCK);
        app.run(); // Главный поток становится Потоком 1
    } catch (const std::exception& e) {
        std::cerr << "Fatal client error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
