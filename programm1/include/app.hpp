#pragma once
#include <string>
#include <thread>
#include <memory>
#include "thread-safe-buffer.hpp"
#include "client-socket.hpp"

class App {
private:
    std::string serverSock_;
    ThreadSafeBuffer buffer_;
    ClientSocket clientSocket_;
    std::thread processingThread_;

    bool isValidInput(const std::string& str);
    void processingThreadRoutine(); // Логика Потока 2
    void sendWithAutoReconnect(const std::string& message);

public:
    explicit App(std::string serverSock);
    ~App();

    void run(); // Вызывается в main (Поток 1)
};
