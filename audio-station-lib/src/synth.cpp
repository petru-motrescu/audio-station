#include <iostream>
#include <memory>
#include <utility>
#include <unordered_map>
#include <vector>
#include "config.hpp"
#include "envelope.hpp"
#include "envelope-renderer.hpp"
#include "note.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct SynthSignal {
    Oscillator oscillator;
    unsigned ticks_since_live;
    unsigned ticks_at_release;
};

struct audiostation::SynthImpl {
    std::vector<SynthSignal> signals;
    std::unordered_map<Note, int> note_signal_ids;
    RenderableEnvelope envelope;
    unsigned sample_rate;
};

double render_signal(
    SynthSignal& signal, 
    RenderableEnvelope& envelope, 
    unsigned sample_rate
);

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

        this->impl->signals.push_back(SynthSignal({
            .oscillator = std::move(oscillator)
        }));

        this->impl->note_signal_ids[note] = signal_id++;
    }

    set_envelope(config.envelope);
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::set_envelope(Envelope envelope) {
    set_renderable_envelope(Envelopes::to_renderable_envelope(envelope));
}

void audiostation::Synth::play(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    // signal.phase = 0; // TODO Reset oscillator phase
    signal.ticks_since_live = 0;
    signal.ticks_at_release = 0;
    signal.oscillator.play();
}

void audiostation::Synth::stop(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    if (this->impl->envelope.release_ticks > 0) {
        signal.ticks_at_release = signal.ticks_since_live;
    } else {
        signal.oscillator.stop();
    }
}

bool audiostation::Synth::is_note_live(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    return this->impl->signals[signal_id].oscillator.is_live();
}

double audiostation::Synth::render() {
    double sample = 0;
    for (auto& signal : this->impl->signals) {
        if (signal.oscillator.is_live()) {
            sample += render_signal(
                signal, 
                this->impl->envelope, 
                this->impl->sample_rate);
        }
    }
    return sample;
}

void audiostation::Synth::set_sample_rate(unsigned sample_rate) {
    this->impl->sample_rate = sample_rate;
}

void audiostation::Synth::set_renderable_envelope(RenderableEnvelope envelope) {
    this->impl->envelope = envelope;
}

double render_signal(
    SynthSignal& signal, 
    RenderableEnvelope& envelope, 
    unsigned sample_rate
) {
    auto sample = signal.oscillator.render();
    auto result = EnvelopeRenderer::render(
        sample,
        signal.ticks_since_live,
        signal.ticks_at_release,
        envelope
    );
    if (!result.live) {
        signal.oscillator.stop();
    };
    signal.ticks_since_live++;
    return result.sample;
}
