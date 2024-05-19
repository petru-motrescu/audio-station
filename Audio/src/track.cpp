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

void audiostation::Track::add_bass_drum(audiostation::BassDrum* bass_drum) {
    this->bass_drums.push_back(bass_drum);
}

void audiostation::Track::add_oscillator(audiostation::Oscillator* oscillator) {
    this->oscillators.push_back(oscillator);
}

void audiostation::Track::add_synth(audiostation::Synth* synth) {
    this->synths.push_back(synth);
}

double audiostation::Track::render() {
    double sample = 0;
    
    for (auto& bass_drum : this->bass_drums) {
        sample += bass_drum->render();
    }

    for (auto& oscillator : this->oscillators) {
        sample += oscillator->render();
    }

    for (auto& synth : this->synths) {
        sample += synth->render();
    }

    return sample;
}
