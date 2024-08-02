#include <iostream>
#include "sequencer.hpp"
using namespace audiostation;

struct audiostation::SequencerImpl {
    SequencerConfig config;
    int live_step_index = -1;
    unsigned ticks_per_step;
    unsigned ticks_since_step_change;
};

Sequencer::Sequencer() : Sequencer(SequencerConfig()) { }

Sequencer::Sequencer(SequencerConfig config) {
    this->impl = std::make_unique<SequencerImpl>();
    this->impl->config = config;
    this->impl->ticks_per_step = config.step_duration * config.sample_rate / 1000.0;
}

Sequencer::Sequencer(const Sequencer& other) {
    this->impl = std::make_unique<SequencerImpl>();
    this->impl->config = other.impl->config;
    this->impl->live_step_index = other.impl->live_step_index;
    this->impl->ticks_per_step = other.impl->ticks_per_step;
    this->impl->ticks_since_step_change = other.impl->ticks_since_step_change;
}

Sequencer::Sequencer(Sequencer&& other) {
    this->impl = std::move(other.impl);
}

Sequencer& Sequencer::operator=(Sequencer&& other) {
    this->impl = std::move(other.impl);
    return *this;
}

Sequencer::~Sequencer() {
    this->impl.reset();
}

void Sequencer::trigger() {
    this->impl->ticks_since_step_change = -1;
    this->impl->live_step_index = -1;
}

bool Sequencer::is_live() const {
    return this->impl->live_step_index >= 0;
}

void Sequencer::tick() {
    this->impl->ticks_since_step_change++;

    if (this->impl->live_step_index >= 0) {
        if (this->impl->ticks_since_step_change < this->impl->ticks_per_step) {
            return;
        }
        
        auto& old_step = impl->config.steps[this->impl->live_step_index];
        for (auto& output : impl->config.outputs) {
            output->release(old_step.note);
        }
    }

    this->impl->ticks_since_step_change = 0;
    this->impl->live_step_index++;
    if (this->impl->live_step_index >= this->impl->config.steps.size()) {
        this->impl->live_step_index = 0;
    }

    auto& new_step = impl->config.steps[this->impl->live_step_index];
    for (auto& output : impl->config.outputs) {
        output->trigger(new_step.note);
    }
}
