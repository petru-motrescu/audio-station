#include <iostream>
#include <utility>
#include <unordered_map>
#include "drum.hpp"
#include "config.hpp"
#include "envelope.hpp"
#include "note.hpp"
#include "renderer.hpp"
using namespace audiostation;

struct audiostation::DrumImpl {
    DrumConfig config;
    double decay_ticks = 0;
    double phase = 0;
    unsigned ticks_since_live = 0;
    bool live = false;
};

audiostation::Drum::Drum() : Drum(DrumConfig()) { }

audiostation::Drum::Drum(DrumConfig config) {
    this->impl = std::make_unique<DrumImpl>();
    this->impl->config = config;
    this->impl->decay_ticks = config.decay_millis * Config::SAMPLE_RATE / 1000.0;
}

audiostation::Drum::~Drum() {
    this->impl.reset();
}

void audiostation::Drum::play() {
    this->impl->phase = 0;
    this->impl->ticks_since_live = 0;
    this->impl->live = true;
}

double audiostation::Drum::render() {
    if (!this->impl->live) {
        return 0;
    }

    double ratio = this->impl->ticks_since_live / this->impl->decay_ticks;
    if (this->impl->ticks_since_live >= this->impl->decay_ticks) {
        ratio = 1;
    }

    auto& config = this->impl->config;
    double frequency = (1 - ratio) * config.atack_frequency + ratio * config.decay_frequency;
    double amplitude = (1 - ratio) * config.amplitude;
    double sample = Renderer::render_wave(config.wave, this->impl->phase) * amplitude;
    this->impl->phase = Renderer::next_phase(this->impl->phase, frequency, Config::SAMPLE_RATE);
    this->impl->ticks_since_live++;

    if (this->impl->ticks_since_live >= this->impl->decay_ticks) {
        this->impl->live = false;
        return 0;
    }

    return sample;
}
