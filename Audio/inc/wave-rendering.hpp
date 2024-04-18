#ifndef AUDIO_STATION_WAVE_RENDERING_HPP
#define AUDIO_STATION_WAVE_RENDERING_HPP

#include "audio-waveform.hpp"

namespace audiostation {
    double render_wave(audiostation::Waveform waveform, double phase);
    double next_phase(double phase, double frequency, unsigned sample_rate);
}

#endif // AUDIO_STATION_WAVE_RENDERING_HPP
