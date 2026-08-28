#include "socket.hpp"

Socket::Socket(int fd)
    : fd_(fd) 
{}

Socket::~Socket()
{
    disconnect();
}

bool Socket::isConnected() const noexcept
{
    return fd_ != -1;
}

void Socket::disconnect() noexcept
{
    if (fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}

Socket::Socket(Socket &&other) noexcept
    : fd_(std::exchange(other.fd_, -1)) 
{}

Socket &Socket::operator=(Socket &&other) noexcept
{
    if (this != &other) {
        disconnect();
        fd_ = std::exchange(other.fd_, -1);
    }
    return *this;
}

int Socket::getFd() const noexcept { return fd_; }
