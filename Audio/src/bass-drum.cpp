#include <iostream>
#include <utility>
#include <unordered_map>
#include "bass-drum.hpp"
#include "config.hpp"
#include "envelope.hpp"
#include "note.hpp"
#include "renderer.hpp"
using namespace audiostation;

struct audiostation::BassDrumImpl {
    BassDrumConfig config;
    double decay_ticks = 0;
    double phase = 0;
    unsigned ticks_since_live = 0;
    bool live = false;
};

audiostation::BassDrum::BassDrum() : BassDrum(BassDrumConfig()) { }

audiostation::BassDrum::BassDrum(BassDrumConfig config) {
    this->impl = std::make_unique<BassDrumImpl>();
    this->impl->config = config;
    this->impl->decay_ticks = config.decay_millis * Config::SAMPLE_RATE / 1000.0;
}

audiostation::BassDrum::~BassDrum() {
    this->impl.reset();
}

void audiostation::BassDrum::play() {
    this->impl->phase = 0;
    this->impl->ticks_since_live = 0;
    this->impl->live = true;
}

double audiostation::BassDrum::render() {
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
    double sample = Renderer::render_wave(config.waveform, this->impl->phase) * amplitude;
    this->impl->phase = Renderer::next_phase(this->impl->phase, frequency, Config::SAMPLE_RATE);
    this->impl->ticks_since_live++;

    // Intentionally stopping when the sample is near 0 to minimize clicking
    if (this->impl->ticks_since_live >= this->impl->decay_ticks) {
        this->impl->live = false;
        return 0;
    }

    return sample;
}
