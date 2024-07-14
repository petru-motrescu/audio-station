#ifndef AUDIO_STATION_RENDERER_HPP
#define AUDIO_STATION_RENDERER_HPP

#include "envelope.hpp"
#include "wave.hpp"

namespace audiostation {

    class WaveRenderer {
    public:
        static double render(audiostation::Wave wave, double phase);
        static double next_phase(double phase, double frequency, unsigned sample_rate);
    };
}

#endif // AUDIO_STATION_RENDERER_HPP
