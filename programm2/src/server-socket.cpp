#include "server-socket.hpp"

#include <sys/un.h>
#include <unistd.h>
#include <filesystem>
#include <string>

ServerSocket::ServerSocket(const std::string& socketPath)
    : Socket(socket(AF_UNIX, SOCK_STREAM, 0)),
      socketPath_(socketPath)
{
    unlink(socketPath_.c_str());

    sockaddr_un address{};
    address.sun_family = AF_UNIX;
    
    strncpy(address.sun_path, socketPath.c_str(), sizeof(address.sun_path) - 1);

    if (bind(fd_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
        throw std::runtime_error("Error binding UNIX socket");
    }

    if (listen(fd_, SOMAXCONN) < 0) {
        throw std::runtime_error("Error listening");
    }
}

ServerSocket::~ServerSocket()
{
    // Удаляем штатно файл в файловой системе
    if (!socketPath_.empty()) {
        unlink(socketPath_.c_str());
    }
}

ServerSocket::ServerSocket(ServerSocket&& other) noexcept
    : Socket(std::move(other)),
      socketPath_(std::move(other.socketPath_)) 
{
    other.socketPath_.clear();
}

ServerSocket& ServerSocket::operator=(ServerSocket&& other) noexcept {
    if (this != &other) {
        if (!socketPath_.empty()) {
            unlink(socketPath_.c_str());    // Удаления прежнего файла сокета
        }
        Socket::operator=(std::move(other));
        socketPath_ = std::move(other.socketPath_);
        other.socketPath_.clear();
    }
    return *this;
}

ClientSocket ServerSocket::acceptClient()
{
    sockaddr_un clientAddr{};
    socklen_t addrLen = sizeof(clientAddr);

    int clientFd = accept(fd_, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
    if (clientFd < 0) {
        throw std::runtime_error("Server couldn't accept new client connection");
    }

    return ClientSocket(clientFd);
}
