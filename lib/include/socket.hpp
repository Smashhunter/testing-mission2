#pragma once
#include <unistd.h>
#include <utility>
#include <stdexcept>

class Socket {
protected:
    int fd_ = -1;

public:
    explicit Socket(int fd);

    virtual ~Socket();

    // Запрещаем копирование, чтобы два объекта не закрыли один дескриптор
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // Разрешаем перемещение владения
    Socket(Socket&& other) noexcept;
    Socket& operator=(Socket&& other) noexcept;

    int getFd() const noexcept;
    bool isConnected() const noexcept;
    void disconnect() noexcept;
};
