#include <iostream>
#include <utility>
#include <unordered_map>
#include "config.hpp"
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

double render_signal(SynthSignal& signal, RenderableEnvelope& envelope);

audiostation::Synth::Synth() {
    this->impl = std::make_unique<SynthImpl>();
    this->impl->sample_rate = Config::SAMPLE_RATE;
    
    int signal_id = 0;
    for (auto& note : Notes::piano_notes) {
        this->impl->signals.push_back({ 
            .waveform = Waveform::Square,
            .frequency = Notes::get_frequency(note),
            .amplitude = 0.2,
            .ticks_since_live = 0
        });
        this->impl->note_signal_ids[note] = signal_id++;
    }

    set_envelope({
        .atack_millis = 10,
        .decay_millis = 100,
        .sustain_level = 0.1,
        .release_millis = 2000
    });
}

audiostation::Synth::~Synth() {
    this->impl.reset();
}

void audiostation::Synth::set_envelope(Envelope envelope) {
    this->impl->envelope = Envelopes::to_renderable_envelope(envelope);
}

void audiostation::Synth::play_note(Note note) {
    auto signal_id = this->impl->note_signal_ids[note];
    auto& signal = this->impl->signals[signal_id];
    signal.phase = 0;
    signal.ticks_since_live = 0;
    signal.ticks_at_release = -1;
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
            sample += render_signal(signal, this->impl->envelope);
        }
    }
    return sample;
}

double render_signal(SynthSignal& signal, RenderableEnvelope& envelope) {
    double sample = Renderer::render_wave(signal.waveform, signal.phase) * signal.amplitude;
    auto result = Renderer::render_enveloped_sample(
        sample,
        signal.ticks_since_live,
        signal.ticks_at_release,
        envelope
    );
    sample = result.sample;
    signal.live = result.live;
    signal.phase = Renderer::next_phase(signal.phase, signal.frequency, Config::SAMPLE_RATE);
    signal.ticks_since_live++;
    return sample;
}