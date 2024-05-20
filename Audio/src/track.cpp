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

void audiostation::Track::add_instrument(Instrument* instrument) {
    this->instruments.push_back(instrument);
}

double audiostation::Track::render() {
    double sample = 0;
    
    for (auto& instrument : this->instruments) {
        sample += instrument->render();
    }

    return sample;
}
