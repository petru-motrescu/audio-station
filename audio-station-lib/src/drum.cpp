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
    double total_ticks = 0;
    double attack_phase = 0;
    double release_phase = 0;
    unsigned ticks_since_live = 0;
    bool live = false;
};

audiostation::Drum::Drum() : Drum(DrumConfig()) { }

audiostation::Drum::Drum(DrumConfig config) {
    this->impl = std::make_unique<DrumImpl>();
    this->impl->config = config;
    this->impl->total_ticks = config.duration * Config::SAMPLE_RATE / 1000.0;
}

audiostation::Drum::~Drum() {
    this->impl.reset();
}

void audiostation::Drum::play() {
    this->impl->attack_phase = 0;
    this->impl->release_phase = 0;
    this->impl->ticks_since_live = 0;
    this->impl->live = true;
}

double audiostation::Drum::render() {
    if (!this->impl->live) {
        return 0;
    }

    double ratio = this->impl->ticks_since_live / this->impl->total_ticks;
    if (this->impl->ticks_since_live >= this->impl->total_ticks) {
        ratio = 1;
    }

    auto& config = this->impl->config;
    double frequency = (1 - ratio) * config.attack.frequency + ratio * config.release.frequency;
    double attack_amplitude = (1 - ratio) * config.attack.amplitude;
    double release_amplitude = (1 - ratio) * config.release.amplitude;
    double attack_sample = Renderer::render_wave(config.attack.wave, this->impl->attack_phase) * attack_amplitude;
    double release_sample = Renderer::render_wave(config.release.wave, this->impl->release_phase) * release_amplitude;
    this->impl->attack_phase = Renderer::next_phase(this->impl->attack_phase, frequency, Config::SAMPLE_RATE);
    this->impl->release_phase = Renderer::next_phase(this->impl->release_phase, frequency, Config::SAMPLE_RATE);
    double sample = (1 - ratio) * attack_sample + ratio * release_sample;

    this->impl->ticks_since_live++;

    if (this->impl->ticks_since_live >= this->impl->total_ticks) {
        this->impl->live = false;
        return 0;
    }

    return sample;
}
