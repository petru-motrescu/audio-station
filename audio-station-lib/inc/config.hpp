#ifndef AUDIO_STATION_CONFIG_HPP
#define AUDIO_STATION_CONFIG_HPP

namespace audiostation {

    struct Config {
        static constexpr unsigned SAMPLE_RATE = 44100;
        static constexpr unsigned BUFFER_SIZE = 512;
        static constexpr double MAX_AMPLITUDE = +1.0;
        static constexpr double MIN_AMPLITUDE = -1.0;
    };
}

#endif // AUDIO_STATION_CONFIG_HPP
