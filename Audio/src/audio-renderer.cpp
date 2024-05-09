#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <vector>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-signal.hpp"
#include "audio-renderer.hpp"
#include "wave-rendering.hpp"
using namespace audiostation;

struct audiostation::AudioRendererImpl {
    AudioRendererImpl(unsigned sample_rate);
    unsigned sample_rate;
    std::vector<AudioSignal> signals;
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
    for (AudioSignal& signal : this->impl->signals) {
        sample += render_wave(signal.waveform, signal.phase) * signal.amplitude;
        signal.phase = next_phase(signal.phase, signal.frequency, this->impl->sample_rate);
    }
    return sample;
}

void audiostation::AudioRenderer::add(audiostation::AudioSignal signal) {
    this->impl->signals.push_back(signal);
}

void audiostation::AudioRenderer::add(std::vector<audiostation::AudioSignal> signals) {
    this->impl->signals.insert(
        std::end(this->impl->signals), 
        std::begin(signals), 
        std::end(signals)
    );
}