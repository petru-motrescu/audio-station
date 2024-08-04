#include <iostream>
#include "mixer.hpp"
using namespace audiostation;

Mixer::Mixer() { }

Mixer::Mixer(std::vector<Track> tracks) {
    this->tracks = tracks;
}

double Mixer::render() {
    double sample = 0;
    
    for (auto& track : this->tracks) {
        if (track.instrument != nullptr) {
            if (track.sequencer != nullptr) {
                track.sequencer->render(*track.instrument);
            }

            double instrument_sample = track.instrument->render();
            sample += instrument_sample;
            for (auto& effect : track.effects) {
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
