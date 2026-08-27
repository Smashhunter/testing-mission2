#pragma once
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <array>
#include "socket.hpp"
#include "lib.hpp"

class ClientSocket : public Socket {
public:
    using Socket::Socket;

    // Читаем в цикле, пока клиент подключен
    void processMessages();
};
