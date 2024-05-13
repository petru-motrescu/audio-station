#include <iostream>
#include <utility>
#include "audio-signal.hpp"
#include "synth.hpp"
using namespace audiostation;

struct audiostation::SynthImpl {
    std::unordered_map<Note, AudioSignal> signals;
};

audiostation::Synth::Synth() {
    this->impl = std::make_unique<SynthImpl>();
    for (int i = Notes::to_int(Synth::FIRST_NOTE); i <= Notes::to_int(Synth::LAST_NOTE); i++) {
        this->impl->signals[Notes::from_int(i)] = AudioSignal();
    }
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::play_note(Note note) {
    this->impl->signals[note].live = true;
}

void audiostation::Synth::stop_note(Note note) {
    this->impl->signals[note].live = false;
}

bool audiostation::Synth::is_note_live(Note note) {
    return this->impl->signals[note].live;
}
