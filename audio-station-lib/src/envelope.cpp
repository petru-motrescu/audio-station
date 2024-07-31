#include <iostream>
#include "envelope.hpp"
using namespace audiostation;

struct audiostation::EnvelopeImpl {
    double attack_ticks;
    double decay_ticks;
    double sustain_level;
    double release_ticks;
    unsigned ticks_since_live;
    unsigned ticks_at_release;
    bool is_live;
};

Envelope::Envelope(EnvelopeConfig config) {
    this->impl = std::make_unique<EnvelopeImpl>();
    this->impl->attack_ticks = config.attack_duration * config.sample_rate / 1000.0;
    this->impl->decay_ticks = config.decay_duration * config.sample_rate / 1000.0;
    this->impl->sustain_level = config.sustain_level;
    this->impl->release_ticks = config.release_duration * config.sample_rate / 1000.0;
}

Envelope::Envelope(const Envelope& other) {
    this->impl = std::make_unique<EnvelopeImpl>();
    this->impl->attack_ticks = other.impl->attack_ticks;
    this->impl->decay_ticks = other.impl->decay_ticks;
    this->impl->sustain_level = other.impl->sustain_level;
    this->impl->release_ticks = other.impl->release_ticks;
}

Envelope::Envelope(Envelope&& other) {
    this->impl = std::move(other.impl);
}

Envelope& Envelope::operator=(Envelope&& other) {
    this->impl = std::move(other.impl);
    return *this;
}

Envelope::~Envelope() {
    this->impl.reset();
}

void Envelope::engage() {
    this->impl->ticks_since_live = 0;
    this->impl->ticks_at_release = 0;
    this->impl->is_live = true;
}

void Envelope::release() {
    this->impl->ticks_at_release = this->impl->ticks_since_live;
}

bool Envelope::is_live() const {
    return this->impl->is_live;
}

double Envelope::render(double sample) {
    const auto& impl = this->impl;
    double new_sample = 0;

    if (impl->ticks_since_live < impl->attack_ticks) {
        new_sample = sample * impl->ticks_since_live / impl->attack_ticks;
    } else if (impl->ticks_since_live < (impl->attack_ticks + impl->decay_ticks)) {
        auto ticks = impl->ticks_since_live - impl->attack_ticks;
        auto ratio = ticks / impl->decay_ticks;
        new_sample = (1 - ratio + ratio * impl->sustain_level) * sample;
    } else if (impl->ticks_at_release == 0) {
        new_sample = impl->sustain_level * sample;
    } else if (impl->ticks_since_live < (impl->ticks_at_release + impl->release_ticks)) {
        auto ticks = impl->ticks_since_live - impl->ticks_at_release;
        new_sample = (1 - ticks / impl->release_ticks) * impl->sustain_level * sample;
    } else {
        this->impl->is_live = false;
        new_sample = 0;
    }

    impl->ticks_since_live++;

    return new_sample;
}
