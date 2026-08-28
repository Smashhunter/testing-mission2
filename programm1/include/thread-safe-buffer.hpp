#pragma once
#include <string>
#include <mutex>
#include <condition_variable>

class ThreadSafeBuffer {
private:
    std::string buffer_;
    bool dataReady_ = false;
    bool stopFlag_ = false;
    mutable std::mutex mutex_;
    std::condition_variable cv_;

public:
    void push(const std::string& data);

    // Возвращает false, если получен сигнал остановки приложения
    bool pop(std::string& outData);

    void stop();
};
