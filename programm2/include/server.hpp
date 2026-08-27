#pragma once
#include <iostream>
#include <string>
#include "server-socket.hpp"
#include "client-socket.hpp"

class Server {
private:
    ServerSocket serverSocket_;

public:
    explicit Server(const std::string& path);

    void start();
};
