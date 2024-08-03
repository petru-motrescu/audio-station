#include <iostream>
#include "oscillator.hpp"
#include "project.hpp"
#include "synth.hpp"
using namespace audiostation;

Project::Project() : Project(ProjectConfig()) {}

Project::Project(ProjectConfig config) {
    this->config = config;
}

double Project::render() {
    double sample = 0;
    
    for (auto& track : this->config.tracks) {
        if (track->instrument != nullptr) {
            if (track->sequencer != nullptr) {
                track->sequencer->render(*track->instrument);
            }

            double instrument_sample = track->instrument->render();
            sample += instrument_sample;
            for (auto& effect : track->effects) {
                sample += effect->render(instrument_sample);
            }
        }
    }

    this->tick += 1;

    if (sample > Config::MAX_AMPLITUDE) {
        std::cout << "Clipping!" << std::endl;
        return Config::MAX_AMPLITUDE;
    }

    if (sample < Config::MIN_AMPLITUDE) {
        std::cout << "Clipping!" << std::endl;
        return Config::MIN_AMPLITUDE;
    }

    return sample;
}
