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

    ClientSocket();

    // Метод подключения к UNIX сокету сервера (Программы №2)
    void connectTo(const std::string& socketPath);

    // Метод надежной отправки строки (добавляет '\n' в конец)
    void sendData(const std::string& data);

    // Читаем в цикле, пока клиент подключен
    void processMessages();
};
