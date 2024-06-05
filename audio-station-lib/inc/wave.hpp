#ifndef AUDIO_STATION_WAVE_HPP
#define AUDIO_STATION_WAVE_HPP

namespace audiostation {

    enum class Wave : int {
        Sine = 0,
        Square = 1,
        Triangle = 2,
        Noise = 3,
    };
}

#endif // AUDIO_STATION_WAVE_HPP
