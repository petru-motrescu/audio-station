#include <iostream>
#include <utility>
#include <unordered_map>
#include <vector>
#include "config.hpp"
#include "envelope.hpp"
#include "envelope-renderer.hpp"
#include "note.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct SynthSignal {
    audiostation::Wave wave;
    double frequency;
    double amplitude;
    double phase;
    unsigned ticks_since_live;
    unsigned ticks_at_release;
    bool live;
};

struct audiostation::SynthImpl {
    std::vector<SynthSignal> signals;
    std::unordered_map<Note, int> note_signal_ids;
    RenderableEnvelope envelope;
    unsigned sample_rate;
};

double render_signal(SynthSignal& signal, RenderableEnvelope& envelope, unsigned sample_rate);

audiostation::Synth::Synth() : Synth(SynthConfig()) { }

audiostation::Synth::Synth(SynthConfig config) {
    this->impl = std::make_unique<SynthImpl>();
    this->impl->sample_rate = Config::SAMPLE_RATE;
    
    int signal_id = 0;
    for (auto& note : Notes::piano_notes) {
        this->impl->signals.push_back({ 
            .wave = config.wave,
            .frequency = Notes::get_frequency(note),
            .amplitude = config.amplitude,
            .ticks_since_live = 0
        });
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

void audiostation::Synth::play_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    signal.phase = 0;
    signal.ticks_since_live = 0;
    signal.ticks_at_release = 0;
    signal.live = true;
}

void audiostation::Synth::stop_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    if (this->impl->envelope.release_ticks > 0) {
        signal.ticks_at_release = signal.ticks_since_live;
    } else {
        signal.live = false;
    }
}

bool audiostation::Synth::is_note_live(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    return this->impl->signals[signal_id].live;
}

double audiostation::Synth::render() {
    double sample = 0;
    for (auto& signal : this->impl->signals) {
        if (signal.live) {
            sample += render_signal(signal, this->impl->envelope, this->impl->sample_rate);
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

double render_signal(SynthSignal& signal, RenderableEnvelope& envelope, unsigned sample_rate) {
    double sample = WaveRenderer::render(signal.wave, signal.phase) * signal.amplitude;
    auto result = EnvelopeRenderer::render(
        sample,
        signal.ticks_since_live,
        signal.ticks_at_release,
        envelope
    );
    signal.live = result.live;
    signal.phase = WaveRenderer::next_phase(signal.phase, signal.frequency, sample_rate);
    signal.ticks_since_live++;
    return result.sample;
}
