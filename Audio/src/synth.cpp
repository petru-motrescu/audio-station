#include <iostream>
#include <utility>
#include <unordered_map>
#include "envelope.hpp"
#include "note.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct SynthSignal {
    audiostation::Waveform waveform;
    double frequency;
    double amplitude;
    double phase;
    unsigned ticks;
    bool live;
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
        .decay = 5000,
        .sustain = 0.005,
        .release = 1
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
    signal.ticks = 0;
    signal.live = true;
}

void audiostation::Synth::stop_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    this->impl->signals[signal_id].live = false;
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
    double sample = WaveRenderer::render_wave(signal.waveform, signal.phase) * signal.amplitude;
    double atack_ticks = envelope.atack * sample_rate / 1000; // TODO Precompute this
    double decay_ticks = envelope.decay * sample_rate / 1000; // TODO Precompute this
    if (signal.ticks < atack_ticks) {
        sample = (signal.ticks / atack_ticks) * sample;
    } else if (signal.ticks < (atack_ticks + decay_ticks)) {
        auto ticks = signal.ticks - atack_ticks;
        sample = (1 - ticks / decay_ticks) * sample + ticks / decay_ticks * envelope.sustain * sample;
    } else {
        sample = envelope.sustain * sample;
    }
    
    signal.phase = WaveRenderer::next_phase(signal.phase, signal.frequency, sample_rate);
    signal.ticks++;
    return sample;
}
