#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <vector>
#include <memory>
#include <AudioToolbox/AudioToolbox.h>
#include "oscillator.hpp"
#include "synth.hpp"
#include "track.hpp"
using namespace audiostation;

void audiostation::Track::add_oscillator(audiostation::Oscillator* oscillator) {
    this->oscillators.push_back(oscillator);
}

void audiostation::Track::add_synth(audiostation::Synth* synth) {
    this->synths.push_back(synth);
}

double audiostation::Track::render() {
    double sample = 0;
    
    for (auto& oscillator : this->oscillators) {
        sample += oscillator->render();
    }

    for (auto& synth : this->synths) {
        sample += synth->render();
    }

    return sample;
}
