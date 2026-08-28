#include "client-socket.hpp"
#include <unistd.h>
#include <stdexcept>
#include <sys/un.h>
#include <cstring>

ClientSocket::ClientSocket() 
    : Socket(-1)
{}

void ClientSocket::connectTo(const std::string& socketPath) {
    if (isConnected()) {
        disconnect(); 
    }

    fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_un address{};
    std::memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    
    std::strncpy(address.sun_path, socketPath.c_str(), sizeof(address.sun_path) - 1);

    if (connect(fd_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        disconnect(); 
        throw std::runtime_error("Connection to Program 2 failed");
    }
}

void ClientSocket::sendData(const std::string& data) {
    if (!isConnected()) {
        throw std::runtime_error("Socket is not connected");
    }

    std::string formattedMessage = data + "\n";
    size_t totalSent = 0;
    size_t bytesLeft = formattedMessage.size();

    // Гарантируем полную отправку всех байт
    while (totalSent < formattedMessage.size()) {
        ssize_t sent = send(fd_, formattedMessage.data() + totalSent, bytesLeft, MSG_NOSIGNAL);
        if (sent == 0) {
            throw std::runtime_error("Connection closed");
        } else if (sent < 0){
            throw std::runtime_error("Socket write error");
        }
        
        totalSent += static_cast<size_t>(sent);
        bytesLeft -= static_cast<size_t>(sent);
    }
}

void ClientSocket::processMessages()
{
    if (!isConnected()) {
        throw std::runtime_error("Cannot process messages: Socket is not connected");
    }
    
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
