#include "app.hpp"

#include <iostream>
#include <iomanip>
#include "lib.hpp"

App::App(std::string serverSock)
    : serverSock_(std::move(serverSock))
{
    // Запускаем Поток 2 при создании класса
    processingThread_ = std::thread(&App::processingThreadRoutine, this);
    
}

App::~App() {
    // Корректная остановка потока при удалении приложения
    buffer_.stop();
    if (processingThread_.joinable()) {
        processingThread_.join();
    }
}

bool App::isValidInput(const std::string& str) {
    if (str.empty() || str.length() > 64) return false;
    for (char c : str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

void App::run() {
    std::string input;
    std::cout << "Type string (only digits, up to 64 symbols):\n";
    while (true) {
        // Ограничиваем ввод максимум 64 символами + 1 для проверки выхода за пределы
        if (!(std::cin >> std::setw(64+1) >> input)) {
            break; // EOF
        }

        // Очищение остатка
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (!isValidInput(input)) {
            std::cerr << "Error: string is not valid!\n";
            continue;
        }

        my_lib::processString(input);
        buffer_.push(input);
    }
}

void App::sendWithAutoReconnect(const std::string& message) {
    constexpr int MAX_RETRIES = 3;

    for (int attempt = 0; attempt < MAX_RETRIES; ++attempt) {
        try {
            if (!clientSocket_.isConnected()) {
                clientSocket_.connectTo(serverSock_);
            }

            // Если соединение разорвано со стороны сервера, sendData выбросит исключение
            clientSocket_.sendData(message); 
            return;

        } catch (const std::exception& e) {
            clientSocket_.disconnect();
        }
    }

    std::cerr << "Warning: Proggram 2 is not avaible. Message skiped.\n";
}

void App::processingThreadRoutine() {
    std::string data;
    
    while (buffer_.pop(data)) {
        std::cout << "[OUT] Data from buffer: " << data << std::endl;

        int sum = my_lib::calculateSum(data);
        std::cout << "[OUT] Calculated sum: " << sum << std::endl;

        sendWithAutoReconnect(std::to_string(sum));
    }
}
