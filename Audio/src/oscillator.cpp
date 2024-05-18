#include <iostream>
#include <utility>
#include "note.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::OscillatorImpl {
    audiostation::Waveform waveform;
    double frequency;
    double amplitude;
    double phase;
    bool is_live;
};

audiostation::Oscillator::Oscillator(
    audiostation::Waveform waveform,
    double frequency,
    double amplitude
) {
    this->impl = std::make_unique<OscillatorImpl>();
    this->impl->waveform = waveform;
    this->impl->frequency = frequency;
    this->impl->amplitude = amplitude;
    this->impl->phase = 0;
    this->impl->is_live = false;
}

audiostation::Oscillator::~Oscillator() {
    this->impl.reset();
}

void audiostation::Oscillator::play() {
    this->impl->is_live = true;
}

void audiostation::Oscillator::stop() {
    this->impl->is_live = false;
}

double audiostation::Oscillator::render(unsigned sample_rate) {
    if (!this->impl->is_live) {
        return 0;
    }

    double sample = WaveRenderer::render_wave(this->impl->waveform, this->impl->phase) * this->impl->amplitude;
    this->impl->phase = WaveRenderer::next_phase(this->impl->phase, this->impl->frequency, sample_rate);
    return sample;
}
