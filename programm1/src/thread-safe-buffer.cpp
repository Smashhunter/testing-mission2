#include "thread-safe-buffer.hpp"

void ThreadSafeBuffer::push(const std::string & data)
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        buffer_ = data;
        dataReady_ = true;
    }
    cv_.notify_one();
}

bool ThreadSafeBuffer::pop(std::string &outData)
 {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [this] { return dataReady_ || stopFlag_; });

    if (stopFlag_ && !dataReady_) {
        return false;
    }

    outData = std::move(buffer_);
    buffer_.clear();
    dataReady_ = false;
    return true;
}

void ThreadSafeBuffer::stop()
{
    {
        std::lock_guard<std::mutex> lock(mutex_);
        stopFlag_ = true;
    }
    cv_.notify_all();
}
