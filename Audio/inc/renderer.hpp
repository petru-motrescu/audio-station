#ifndef AUDIO_STATION_WAVE_RENDERER_HPP
#define AUDIO_STATION_WAVE_RENDERER_HPP

#include "waveform.hpp"

namespace audiostation {

    struct Renderer
    {
        static double render_sine_wave(double phase);
        static double render_square_wave(double phase);
        static double render_wave(audiostation::Waveform waveform, double phase);
        static double next_phase(double phase, double frequency, unsigned sample_rate);
    };
}

#endif // AUDIO_STATION_WAVE_RENDERER_HPP
