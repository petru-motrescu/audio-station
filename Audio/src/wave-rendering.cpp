#include <iostream>
#include "wave-rendering.hpp"
using namespace audiostation;

double render_sine_wave(double phase) {
    return sin(phase);
}

double audiostation::render_wave(Waveform waveform, double phase) {
    switch (waveform) {
        case Waveform::Sine:
            return render_sine_wave(phase);
        default:
            return 0;
    }
}
