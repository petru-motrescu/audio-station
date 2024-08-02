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
    std::vector<Oscillator> oscillators;
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
        std::vector<Oscillator> oscillators;
        auto fundamental_frequency = Notes::get_frequency(note);
        
        auto oscillator = Oscillator({
            .wave = config.wave,
            .frequency = fundamental_frequency,
            .amplitude = config.amplitude,
        });
        oscillators.push_back(oscillator);
        
        auto amplitude = config.amplitude / 4.0;
        for (int i = 0; i < config.harmonics; i++) {
            auto oscillator = Oscillator({
                .wave = config.wave,
                .frequency = fundamental_frequency * (i + 2),
                .amplitude = amplitude,
            });
            oscillators.push_back(oscillator);
            amplitude /= 2.0;
        }

        auto envelope = Envelope(config.envelope);

        this->impl->signals.push_back(SynthSignal({
            .oscillators = std::move(oscillators),
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
    
    for (auto& oscilator : signal.oscillators) {
        oscilator.set_phase(0);
        oscilator.play();
    }
    
    signal.envelope.trigger();
}

void audiostation::Synth::stop(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    signal.envelope.release();
}

bool audiostation::Synth::is_note_live(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    return this->impl->signals[signal_id].oscillators.front().is_live();
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
    double sample = 0.0;
    for (auto& oscillator : signal.oscillators) {
        sample += oscillator.render();
    }

    auto amplitude = signal.envelope.render();
    if (!signal.envelope.is_live()) {
        for (auto& oscillator : signal.oscillators) {
            oscillator.stop();
        }
    };

    return sample * amplitude;
}
