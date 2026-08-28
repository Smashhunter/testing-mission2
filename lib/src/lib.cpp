#include"lib.hpp"
#include <cctype>
#include <algorithm>
#include <stdexcept>

void my_lib::processString(std::string &input)
{
    std::sort(input.begin(), input.end(), std::greater<>());
    std::string result{ "" };
    result.reserve(input.length() * 2);

    for(const char c: input){
        if(c % 2 == 0){
            result.push_back('K');
            result.push_back('B');
        } else {
            result.push_back(c);
        }
    }
    input = std::move(result);
}

int my_lib::calculateSum(const std::string &input)
{
    int sum = 0;
    for(const char c: input){
        if(std::isdigit(static_cast<unsigned char>(c))){
            sum += c - '0';
        }
    }
    return sum;
}

bool my_lib::checkLength(const std::string &input) noexcept
{
    if(input.length() <= 2) return false;
    try{
        return std::stoi(input) % 32 == 0;
    } catch (...){
        return false;
    }
}
