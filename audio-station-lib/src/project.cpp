#include <iostream>
#include "oscillator.hpp"
#include "project.hpp"
#include "synth.hpp"
using namespace audiostation;

Project::Project() : Project(ProjectConfig()) {}

Project::Project(ProjectConfig config) {
    this->config = config;
}

void Project::add_live_instrument(Instrument* instrument) {
    this->config.live_instruments.push_back(instrument);
}

double Project::render() {
    for (auto& sequencer : this->config.sequencers) {
        sequencer->tick();
    }

    for (auto& lane : this->config.lanes) {
        for (auto& block : lane->blocks) {
            for (auto& note : block.notes) {
                if ((note.pos + block.pos) == this->tick) {
                    lane->instrument->trigger(note.note);
                }
                if ((note.pos + note.len + block.pos) == this->tick) {
                    lane->instrument->release(note.note);
                }
            }
        }
    }

    double sample = 0;
    
    for (auto& lane : this->config.lanes) {
        double instrument_sample = lane->instrument->render();
        sample += instrument_sample;
        for (auto& effect : lane->effects) {
            sample += effect->render(instrument_sample);
        }
    }
    
    // TODO Remove live_instruments
    for (auto& live_instrument : this->config.live_instruments) {
        sample += live_instrument->render();
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
