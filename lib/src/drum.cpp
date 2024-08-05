#include <iostream>
#include "drum.hpp"
#include "config.hpp"
#include "envelope.hpp"
#include "note.hpp"
#include "tick.hpp"
using namespace audiostation;

struct audiostation::DrumImpl {
    DrumConfig config;
    std::unique_ptr<Oscillator> opening_oscillator; // TODO No need for pointer here
    std::unique_ptr<Oscillator> closing_oscillator;
    Envelope envelope;
    Tick total_ticks = 0;
    Tick ticks_since_live = 0;
    Tick release_at_tick = 0;
};

audiostation::Drum::Drum() : Drum(DrumConfig()) { }

audiostation::Drum::Drum(DrumConfig config) {
    this->impl = std::make_unique<DrumImpl>();
    this->impl->config = config;

    this->impl->opening_oscillator = std::make_unique<Oscillator>(
        OscillatorConfig({
            .wave = config.opening_signal.wave,
            .frequency = config.opening_signal.frequency,
            .amplitude = config.opening_signal.amplitude,
        }
    ));

    this->impl->closing_oscillator = std::make_unique<Oscillator>(
        OscillatorConfig({
            .wave = config.closing_signal.wave,
            .frequency = config.closing_signal.frequency,
            .amplitude = config.closing_signal.amplitude,
        }
    ));

    this->impl->envelope = Envelope({
        .attack_duration = config.attack_duration,
        .release_duration = config.release_duration,
    });

    auto release_after = config.attack_duration + config.sustain_duration;
    this->impl->release_at_tick = release_after * Config::SAMPLE_RATE / 1000.0;

    auto total_duration = release_after + config.release_duration;
    this->impl->total_ticks = total_duration * Config::SAMPLE_RATE / 1000.0;
}

audiostation::Drum::~Drum() {
    this->impl.reset();
}

void audiostation::Drum::trigger(Note note) {
    this->impl->opening_oscillator->set_phase(0);
    this->impl->closing_oscillator->set_phase(0);
    this->impl->opening_oscillator->trigger();
    this->impl->closing_oscillator->trigger();
    this->impl->envelope.trigger();
    this->impl->ticks_since_live = 0;
}

double audiostation::Drum::render() {
    if (!this->impl->envelope.is_live()) {
        return 0;
    }

    if (this->impl->ticks_since_live == this->impl->release_at_tick) {
        this->impl->envelope.release();
    }

    double ratio = this->impl->ticks_since_live / (double)this->impl->total_ticks;
    if (this->impl->ticks_since_live >= this->impl->total_ticks) {
        ratio = 1;
    }

    auto& opening = this->impl->config.opening_signal;
    auto& closing = this->impl->config.closing_signal;

    double amplitude = (1 - ratio) * opening.amplitude + ratio * closing.amplitude;
    this->impl->opening_oscillator->set_amplitude(amplitude);
    this->impl->closing_oscillator->set_amplitude(amplitude);

    double frequency = (1 - ratio) * opening.frequency + ratio * closing.frequency;
    this->impl->opening_oscillator->set_frequency(frequency);
    this->impl->closing_oscillator->set_frequency(frequency);

    double attack_sample = this->impl->opening_oscillator->render();
    double release_sample = this->impl->closing_oscillator->render();
    double sample = (1 - ratio) * attack_sample + ratio * release_sample;

    this->impl->ticks_since_live++;

    if (!this->impl->envelope.is_live()) {
        this->impl->opening_oscillator->release();
        this->impl->closing_oscillator->release();
        return 0;
    }

    auto envamp = this->impl->envelope.render();
    return sample * envamp;
}
