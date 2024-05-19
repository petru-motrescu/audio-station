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
