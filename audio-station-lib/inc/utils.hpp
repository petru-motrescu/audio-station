#ifndef AUDIO_STATION_UTILS_HPP
#define AUDIO_STATION_UTILS_HPP

#include <iostream>
#include <string>

namespace audiostation {

    void require(bool condition, std::string message) {
        if (!condition) {
            std::cout << message << std::endl;
            abort();
        }
    }
}

#endif // AUDIO_STATION_UTILS_HPP
