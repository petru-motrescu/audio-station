#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "utils.hpp"

void audiostation::require(bool condition, std::string message) {
    if (!condition) {
        std::cout << message << std::endl;
        throw std::invalid_argument(message);
    }
}

void audiostation::sleep_for_seconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void audiostation::sleep_for_millis(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}