#include <iostream>
#include "drum.hpp"
#include "config.hpp"
#include "envelope.hpp"
#include "note.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::DrumImpl {
    DrumConfig config;
    std::unique_ptr<Oscillator> attack_oscillator;
    std::unique_ptr<Oscillator> release_oscillator;
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
    this->impl->attack_oscillator = std::make_unique<Oscillator>(config.attack);
    this->impl->release_oscillator = std::make_unique<Oscillator>(config.release);
    this->impl->total_ticks = config.duration * Config::SAMPLE_RATE / 1000.0;
}

audiostation::Drum::~Drum() {
    this->impl.reset();
}

void audiostation::Drum::play(Note note) {
    this->impl->attack_oscillator->play();
    this->impl->release_oscillator->play();
    this->impl->attack_phase = 0; // TODO Reset oscillator phase
    this->impl->release_phase = 0; // TODO Reset oscillator phase
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
    this->impl->attack_oscillator->set_amplitude((1 - ratio) * config.attack.amplitude);
    this->impl->release_oscillator->set_amplitude((1 - ratio) * config.release.amplitude);

    double frequency = (1 - ratio) * config.attack.frequency + ratio * config.release.frequency;
    this->impl->attack_oscillator->set_frequency(frequency);
    this->impl->release_oscillator->set_frequency(frequency);

    double attack_sample = this->impl->attack_oscillator->render();
    double release_sample = this->impl->release_oscillator->render();
    double sample = (1 - ratio) * attack_sample + ratio * release_sample;

    this->impl->ticks_since_live++;

    if (this->impl->ticks_since_live >= this->impl->total_ticks) {
        this->impl->attack_oscillator->stop();
        this->impl->release_oscillator->stop();
        this->impl->live = false;
        return 0;
    }

    return sample;
}
