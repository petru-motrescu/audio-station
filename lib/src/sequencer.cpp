#include <iostream>
#include "sequencer.hpp"
#include "utils.hpp"
using namespace audiostation;

struct audiostation::SequencerImpl {
    SequencerConfig config;
    Tick tick = 0;
};

Sequencer::Sequencer() : Sequencer(SequencerConfig()) { }

Sequencer::Sequencer(SequencerConfig config) {
    this->impl = std::make_unique<SequencerImpl>();
    this->impl->config = config;
    if (config.loop_enabled) {
        require(
            config.loop_length >= 2, 
            "The minimum loop length of a sequencer is 2 ticks. "
            "A second tick is needed to release a triggered note."
        );
    }
}

Sequencer::Sequencer(const Sequencer& other) {
    this->impl = std::make_unique<SequencerImpl>();
    this->impl->config = other.impl->config;
    this->impl->tick = other.impl->tick;
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
    // TODO
}

bool Sequencer::is_live() const {
    return true; // TODO
}

void Sequencer::render(Playable& output) {
    for (auto& block : this->impl->config.blocks) {
        for (auto& note : block.notes) {
            if ((note.offset + block.offset) == this->impl->tick) {
                output.trigger(note.note);
            }
            if ((note.offset + note.length + block.offset) == this->impl->tick) {
                output.release(note.note);
            }
        }
    }

    this->impl->tick++;

    if (this->impl->config.loop_enabled) {
        if (this->impl->tick >= this->impl->config.loop_length) {
            this->impl->tick = 0;
        }
    }
}
