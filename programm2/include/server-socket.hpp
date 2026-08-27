#pragma once
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include "socket.hpp"
#include "client-socket.hpp"

class ServerSocket : public Socket {
private:
    std::string socketPath_;
public:
    explicit ServerSocket(const std::string& socketPath);
    ~ServerSocket() override;

    ServerSocket(const ServerSocket&) = delete;
    ServerSocket& operator=(const ServerSocket&) = delete;

    ServerSocket(ServerSocket&& other) noexcept;
    ServerSocket& operator=(ServerSocket&& other) noexcept;

    ClientSocket acceptClient();
};
