#include "socket.hpp"

Socket::Socket(int fd)
    : fd_(fd) 
{
    if (fd_ < 0) throw std::runtime_error("Invalid socket descriptor");
}

Socket::~Socket()
{
    if (fd_ >= 0) {
        close(fd_);
    }
}

Socket::Socket(Socket &&other) noexcept
    : fd_(std::exchange(other.fd_, -1)) 
{}

Socket &Socket::operator=(Socket &&other) noexcept
{
    if (this != &other) {
        if (fd_ >= 0) close(fd_);
        fd_ = std::exchange(other.fd_, -1);
    }
    return *this;
}

int Socket::getFd() const noexcept { return fd_; }
