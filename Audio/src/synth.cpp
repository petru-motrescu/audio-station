#include <iostream>
#include <utility>
#include <unordered_map>
#include "envelope.hpp"
#include "note.hpp"
#include "renderer.hpp"
#include "synth.hpp"
using namespace audiostation;

struct SynthSignal {
    audiostation::Waveform waveform;
    double frequency;
    double amplitude;
    double phase;
    unsigned ticks;
    bool live;
    long released_at_ticks;
};

struct audiostation::SynthImpl {
    std::vector<SynthSignal> signals;
    std::unordered_map<Note, int> note_signal_ids;
    Envelope envelope;
};

double render_signal(SynthSignal& signal, Envelope& envelope, unsigned sample_rate);

audiostation::Synth::Synth() {
    this->impl = std::make_unique<SynthImpl>();
    int signal_id = 0;
    for (auto& note : Notes::piano_notes) {
        this->impl->signals.push_back({ 
            .waveform = Waveform::Square,
            .frequency = Notes::get_frequency(note),
            .amplitude = 0.2,
            .ticks = 0
        });
        this->impl->note_signal_ids[note] = signal_id++;
    }

    this->impl->envelope = {
        .atack = 10,
        .decay = 100,
        .sustain = 0.1,
        .release = 2000
    };
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::set_envelope(Envelope envelope) {
    this->impl->envelope = envelope;
}

void audiostation::Synth::play_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    signal.phase = 0;
    signal.ticks = 0;
    signal.live = true;
    signal.released_at_ticks = -1;
}

void audiostation::Synth::stop_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    if (this->impl->envelope.release > 0) {
        signal.released_at_ticks = signal.ticks;
    } else {
        signal.live = false;
    }
}

bool audiostation::Synth::is_note_live(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    return this->impl->signals[signal_id].live;
}

double audiostation::Synth::render(unsigned sample_rate) {
    double sample = 0;
    for (auto& signal : this->impl->signals) {
        if (signal.live) {
            sample += render_signal(signal, this->impl->envelope, sample_rate);
        }
    }
    return sample;
}

double render_signal(SynthSignal& signal, Envelope& envelope, unsigned sample_rate) {
    double sample = Renderer::render_wave(signal.waveform, signal.phase) * signal.amplitude;
    double atack_ticks = envelope.atack * sample_rate / 1000; // TODO Precompute this
    double decay_ticks = envelope.decay * sample_rate / 1000; // TODO Precompute this
    double release_ticks = envelope.release * sample_rate / 1000; // TODO Precompute this
    
    if (signal.ticks < atack_ticks) {
        sample = (signal.ticks / atack_ticks) * sample;
    } else if (signal.ticks < (atack_ticks + decay_ticks)) {
        auto ticks = signal.ticks - atack_ticks;
        sample = (1 - ticks / decay_ticks) * sample + ticks / decay_ticks * envelope.sustain * sample;
    } else if (signal.released_at_ticks < 0) {
        sample = envelope.sustain * sample;
    } else if (signal.ticks < (signal.released_at_ticks + release_ticks)) {
        auto ticks = signal.ticks - signal.released_at_ticks;
        sample = (1 - ticks / release_ticks) * envelope.sustain * sample;
    } else {
        signal.live = false;
        return 0;
    }

    signal.phase = Renderer::next_phase(signal.phase, signal.frequency, sample_rate);
    signal.ticks++;
    return sample;
}
