#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-renderer.hpp"
#include "wave-rendering.hpp"
using namespace audiostation;

struct audiostation::AudioRendererImpl {
    AudioRendererImpl(unsigned sample_rate);
    double phase;
    unsigned sample_rate;
};

audiostation::AudioRendererImpl::AudioRendererImpl(unsigned sample_rate) {
    this->sample_rate = sample_rate;
}

audiostation::AudioRenderer::AudioRenderer(unsigned sample_rate) {
    this->impl = std::make_unique<AudioRendererImpl>(sample_rate);
}

audiostation::AudioRenderer::~AudioRenderer() = default;

double audiostation::AudioRenderer::render() {
    auto frequency = 100;
    auto amplitude = 0.5;
    double sample = render_wave(Waveform::Sine, impl->phase) * amplitude;
    impl->phase = next_phase(impl->phase, frequency, impl->sample_rate);
    return sample;
}
