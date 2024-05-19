#include <iostream>
#include <cmath>
#include "renderer.hpp"
using namespace audiostation;

constexpr double TWO_PI = 2 * M_PI;

double audiostation::Renderer::render_sine_wave(double phase) {
    return sin(phase);
}

double audiostation::Renderer::render_square_wave(double phase) {
    if (sin(phase) < 0) {
        return -1;
    } else {
        return +1;
    }
}

double audiostation::Renderer::render_wave(Waveform waveform, double phase) {
    switch (waveform) {
        case Waveform::Sine:
            return render_sine_wave(phase);
        case Waveform::Square:
            return render_square_wave(phase);
        default:
            return 0;
    }
}

double audiostation::Renderer::next_phase(double phase, double frequency, unsigned sample_rate) {
    double next_phase = phase + TWO_PI * frequency / sample_rate;

    if (next_phase >= TWO_PI) {
        next_phase -= TWO_PI;
    }

    if (next_phase < 0.0) {
        next_phase += TWO_PI;
    }

    return next_phase;
}

EnvelopedSample audiostation::Renderer::render_enveloped_sample(
    double sample,
    unsigned ticks_since_live,
    unsigned ticks_at_release,
    RenderableEnvelope& envelope
) {
    double new_sample = sample;
    bool live = true;

    if (ticks_since_live < envelope.atack_ticks) {
        new_sample = (ticks_since_live / envelope.atack_ticks) * sample;
    } else if (ticks_since_live < (envelope.atack_ticks + envelope.decay_ticks)) {
        auto ticks = ticks_since_live - envelope.atack_ticks;
        auto ratio = ticks / envelope.decay_ticks;
        new_sample = (1 - ratio + ratio * envelope.sustain_level) * sample;
    } else if (ticks_at_release < 0) {
        new_sample = envelope.sustain_level * sample;
    } else if (ticks_since_live < (ticks_at_release + envelope.release_ticks)) {
        auto ticks = ticks_since_live - ticks_at_release;
        new_sample = (1 - ticks / envelope.release_ticks) * envelope.sustain_level * sample;
    } else {
        live = false;
        new_sample = 0;
    }

    return { .sample = new_sample, .live = live };
}
