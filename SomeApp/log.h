#ifndef LOG_H
#define LOG_H
#include <string>

namespace some {
    auto getCurrentTime() -> std::string;
    auto log(const std::string &message) -> void;
}


#endif //LOG_H
