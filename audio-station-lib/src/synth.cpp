#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>
#include <vector>
#include "config.hpp"
#include "envelope.hpp"
#include "note.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
using namespace audiostation;

struct SynthSignal {
    Oscillator oscillator;
    Envelope envelope;
};

struct audiostation::SynthImpl {
    std::vector<SynthSignal> signals;
    std::unordered_map<Note, int> note_signal_ids;
    unsigned sample_rate;
};

double render_signal(SynthSignal& signal);

audiostation::Synth::Synth() : Synth(SynthConfig()) { }

audiostation::Synth::Synth(SynthConfig config) {
    this->impl = std::make_unique<SynthImpl>();
    this->impl->sample_rate = Config::SAMPLE_RATE;
    
    int signal_id = 0;
    for (auto& note : Notes::piano_notes) {
        auto oscillator = Oscillator({
            .wave = config.wave,
            .frequency = Notes::get_frequency(note),
            .amplitude = config.amplitude
        });

        auto envelope = Envelope(config.envelope);

        this->impl->signals.push_back(SynthSignal({
            .oscillator = std::move(oscillator),
            .envelope = std::move(envelope)
        }));

        this->impl->note_signal_ids[note] = signal_id++;
    }
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::play(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    // signal.phase = 0; // TODO Reset oscillator phase
    signal.oscillator.play();
    signal.envelope.engage();
}

void audiostation::Synth::stop(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    signal.envelope.release();
}

bool audiostation::Synth::is_note_live(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    return this->impl->signals[signal_id].oscillator.is_live();
}

double audiostation::Synth::render() {
    double sample = 0;
    for (auto& signal : this->impl->signals) {
        if (signal.envelope.is_live()) {
            sample += render_signal(signal);
        }
    }
    return sample;
}

double render_signal(SynthSignal& signal) {
    auto sample = signal.oscillator.render();
    auto result = signal.envelope.render(sample);
    if (!signal.envelope.is_live()) {
        signal.oscillator.stop();
    };
    return result;
}
