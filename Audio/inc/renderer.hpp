#ifndef AUDIO_STATION_WAVE_RENDERER_HPP
#define AUDIO_STATION_WAVE_RENDERER_HPP

#include "envelope.hpp"
#include "waveform.hpp"

namespace audiostation {

    struct EnvelopedSample {
        double sample;
        bool live;
    };

    struct Renderer
    {
        static double render_sine_wave(double phase);
        static double render_square_wave(double phase);
        static double render_triangle_wave(double phase);
        static double render_noise_wave();
        static double render_wave(audiostation::Waveform waveform, double phase);
        static double next_phase(double phase, double frequency, unsigned sample_rate);
        
        static EnvelopedSample render_enveloped_sample(
            double sample,
            unsigned ticks_since_live,
            unsigned ticks_at_release,
            RenderableEnvelope& envelope
        );
    };
}

#endif // AUDIO_STATION_WAVE_RENDERER_HPP
