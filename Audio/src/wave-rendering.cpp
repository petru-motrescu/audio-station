#include <iostream>
#include <cmath>
#include "wave-rendering.hpp"
using namespace audiostation;

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

double audiostation::render_wave(Waveform waveform, double phase) {
    switch (waveform) {
        case Waveform::Sine:
            return render_sine_wave(phase);
        case Waveform::Square:
            return render_square_wave(phase);
        default:
            return 0;
    }
}
