#include "log.h"

#include <chrono>
#include <format>
#include <iostream>

auto some::getCurrentTime() -> std::string {
    auto now = std::chrono::system_clock::now();
    std::time_t tn = std::chrono::system_clock::to_time_t(now);
    std::tm *lt = std::localtime(&tn);
    std::stringstream ss;
    ss << std::put_time(lt, "%H:%M:%S");
    return ss.str();
}

auto some::log(const std::string &message) -> void {
    std::cout << std::format("[{}] {}", getCurrentTime(), message)
            << std::endl;
}
