#ifndef AUDIO_STATION_UTILS_HPP
#define AUDIO_STATION_UTILS_HPP

#include <string>

namespace audiostation {
    void require(bool condition, std::string message);
    void sleep_for_seconds(int seconds);
    void sleep_for_millis(int millis);
}

#endif // AUDIO_STATION_UTILS_HPP
