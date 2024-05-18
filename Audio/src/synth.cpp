#include <iostream>
#include <utility>
#include <unordered_map>
#include "note.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct SynthSignal {
    audiostation::Waveform waveform;
    double frequency;
    double amplitude;
    double phase;
    bool live;
};

struct audiostation::SynthImpl {
    std::vector<SynthSignal> signals;
    std::unordered_map<Note, int> note_signal_ids;
};

audiostation::Synth::Synth() {
    this->impl = std::make_unique<SynthImpl>();
    int signal_id = 0;
    for (auto& note : Notes::piano_notes) {
        this->impl->signals.push_back({ 
            .waveform = Waveform::Square, 
            .frequency = Notes::get_frequency(note), 
            .amplitude = 0.1
        });
        this->impl->note_signal_ids[note] = signal_id++;
    }
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::play_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    this->impl->signals[signal_id].live = true;
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
            sample += WaveRenderer::render_wave(signal.waveform, signal.phase) * signal.amplitude;
            signal.phase = WaveRenderer::next_phase(signal.phase, signal.frequency, sample_rate);
        }
    }
    return sample;
}
