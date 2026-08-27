#include "client-socket.hpp"

void ClientSocket::processMessages()
{
    constexpr size_t BUFFER_SIZE = 1024;
    std::array<char, BUFFER_SIZE> buffer;
    std::string streamBuffer;
    streamBuffer.reserve(BUFFER_SIZE);

    while (true) {
        ssize_t bytesRead = read(fd_, buffer.data(), buffer.size());
        
        if (bytesRead > 0) {
            streamBuffer.append(buffer.data(), bytesRead);
            size_t pos = 0;
            while ((pos = streamBuffer.find('\n')) != std::string::npos) {
                std::string message = streamBuffer.substr(0, pos);
                streamBuffer.erase(0, pos + 1);

                if (message.empty()) continue;

                if (my_lib::checkLength(message)) {
                    std::cout << "Success data: " << message << std::endl;
                } else {
                    std::cerr << "Error: invalid data" << std::endl;
                }
            }
        } 
        else if (bytesRead == 0) {
            break;  // Клиент отключился
        } 
        else {
            throw std::runtime_error("Error reading from socket");
        }
    }
}
