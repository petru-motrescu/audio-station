#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <vector>
#include <memory>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-renderer.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

struct audiostation::AudioRendererImpl {
    AudioRendererImpl(unsigned sample_rate);
    unsigned sample_rate;
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
