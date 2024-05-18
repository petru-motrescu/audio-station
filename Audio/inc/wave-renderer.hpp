#ifndef AUDIO_STATION_WAVE_RENDERER_HPP
#define AUDIO_STATION_WAVE_RENDERER_HPP

#include "waveform.hpp"

namespace audiostation {

    struct WaveRenderer
    {
        static double render_wave(audiostation::Waveform waveform, double phase);
        static double next_phase(double phase, double frequency, unsigned sample_rate);
    };
}

#endif // AUDIO_STATION_WAVE_RENDERER_HPP
