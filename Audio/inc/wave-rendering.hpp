#ifndef AUDIO_STATION_WAVE_RENDERING_HPP
#define AUDIO_STATION_WAVE_RENDERING_HPP

namespace audiostation {

    enum class Waveform : int {
        Sine = 0,
        Square = 1,
    };

    double render_wave(Waveform waveform, double phase);
    double next_phase(double phase, double frequency, unsigned sample_rate);
}

#endif // AUDIO_STATION_WAVE_RENDERING_HPP
