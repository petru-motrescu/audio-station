#include <iostream>
#include <cmath>
#include "wave-renderer.hpp"
using namespace audiostation;

constexpr double TWO_PI = 2 * M_PI;

double render_sine_wave(double phase);
double render_square_wave(double phase);

double audiostation::WaveRenderer::render_wave(Waveform waveform, double phase) {
    switch (waveform) {
        case Waveform::Sine:
            return render_sine_wave(phase);
        case Waveform::Square:
            return render_square_wave(phase);
        default:
            return 0;
    }
}

double audiostation::WaveRenderer::next_phase(double phase, double frequency, unsigned sample_rate) {
    double next_phase = phase + TWO_PI * frequency / sample_rate;

    if (next_phase >= TWO_PI) {
        next_phase -= TWO_PI;
    }

    if (next_phase < 0.0) {
        next_phase += TWO_PI;
    }

    return next_phase;
}

double render_sine_wave(double phase) {
    return sin(phase);
}

double render_square_wave(double phase) {
    if (sin(phase) < 0) {
        return -1;
    } else {
        return +1;
    }
}
