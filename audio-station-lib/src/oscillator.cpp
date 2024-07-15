#include <iostream>
#include <utility>
#include "config.hpp"
#include "note.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::OscillatorImpl {
    audiostation::Wave wave;
    double frequency;
    double amplitude;
    double phase;
    bool is_live;
};

audiostation::Oscillator::Oscillator(
    audiostation::Wave wave,
    double frequency,
    double amplitude
) {
    this->impl = std::make_unique<OscillatorImpl>();
    this->impl->wave = wave;
    this->impl->frequency = frequency;
    this->impl->amplitude = amplitude;
    this->impl->phase = 0;
    this->impl->is_live = false;
}

audiostation::Oscillator::~Oscillator() {
    this->impl.reset();
}

void audiostation::Oscillator::play(Note note) {
    this->impl->phase = 0;
    this->impl->is_live = true;
}

void audiostation::Oscillator::stop(Note note) {
    this->impl->is_live = false;
}

double audiostation::Oscillator::render() {
    if (!this->impl->is_live) {
        return 0;
    }

    double sample = WaveRenderer::render(this->impl->wave, this->impl->phase) * this->impl->amplitude;
    this->impl->phase = WaveRenderer::next_phase(this->impl->phase, this->impl->frequency, Config::SAMPLE_RATE);
    return sample;
}
