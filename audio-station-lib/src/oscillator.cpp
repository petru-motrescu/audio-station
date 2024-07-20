#include <iostream>
#include <utility>
#include "config.hpp"
#include "note.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::OscillatorImpl {
    OscillatorConfig config;
    bool is_live;
};

audiostation::Oscillator::Oscillator(OscillatorConfig config) {
    this->impl = std::make_unique<OscillatorImpl>();
    this->impl->config = config;
    this->impl->is_live = false;
}

audiostation::Oscillator::~Oscillator() {
    this->impl.reset();
}

void audiostation::Oscillator::play(Note note) {
    this->impl->is_live = true;
}

void audiostation::Oscillator::stop(Note note) {
    this->impl->is_live = false;
}

double audiostation::Oscillator::render() {
    if (!this->impl->is_live) {
        return 0;
    }

    auto& config = this->impl->config;
    double sample = WaveRenderer::render(config.wave, config.phase) * config.amplitude;
    config.phase = WaveRenderer::next_phase(config.phase, config.frequency, Config::SAMPLE_RATE);
    return sample;
}
