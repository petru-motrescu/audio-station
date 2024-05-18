#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <vector>
#include <memory>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-signal.hpp"
#include "audio-renderer.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::AudioRendererImpl {
    AudioRendererImpl(unsigned sample_rate);
    unsigned sample_rate;
    std::vector<AudioSignal> signals;
    std::vector<Oscillator*> oscillators;
    std::vector<Synth*> synths;
};

audiostation::AudioRendererImpl::AudioRendererImpl(unsigned sample_rate) {
    this->sample_rate = sample_rate;
}

audiostation::AudioRenderer::AudioRenderer(unsigned sample_rate) {
    this->impl = std::make_unique<AudioRendererImpl>(sample_rate);
}

audiostation::AudioRenderer::~AudioRenderer() = default;

double audiostation::AudioRenderer::render() {
    double sample = 0;
    
    // TODO: Move to a osciloscope device
    for (AudioSignal& signal : this->impl->signals) {
        if (signal.live) {
            sample += WaveRenderer::render_wave(signal.waveform, signal.phase) * signal.amplitude;
        }
        // Intentionally advancing the phase of silent signals too.
        signal.phase = WaveRenderer::next_phase(signal.phase, signal.frequency, this->impl->sample_rate);
    }

    for (auto oscillator : this->impl->oscillators) {
        sample += oscillator->render(this->impl->sample_rate);
    }

    for (auto synth : this->impl->synths) {
        sample += synth->render(this->impl->sample_rate);
    }

    return sample;
}

void audiostation::AudioRenderer::add_oscillator(audiostation::Oscillator* oscillator) {
    this->impl->oscillators.push_back(oscillator);
}

void audiostation::AudioRenderer::add_synth(audiostation::Synth* synth) {
    this->impl->synths.push_back(synth);
}

void audiostation::AudioRenderer::add_signal(audiostation::AudioSignal signal) {
    this->impl->signals.push_back(signal);
}

void audiostation::AudioRenderer::add_signals(std::vector<audiostation::AudioSignal> signals) {
    this->impl->signals.insert(
        std::end(this->impl->signals), 
        std::begin(signals), 
        std::end(signals)
    );
}

void audiostation::AudioRenderer::set_signal_live(int signal_id, bool live) {
    this->impl->signals[signal_id].live = live;
}
