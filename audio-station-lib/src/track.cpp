#include <iostream>
#include "oscillator.hpp"
#include "synth.hpp"
#include "track.hpp"
using namespace audiostation;

void audiostation::Track::add_live_instrument(Instrument* instrument) {
    this->live_instruments.push_back(instrument);
}

double audiostation::Track::render() {    
    for (auto& lane : this->lanes) {
        for (auto& block : lane->blocks) {
            for (auto& note : block.notes) {
                if ((note.pos + block.pos) == this->tick) {
                    lane->instrument->play(note.note);
                }
                if ((note.pos + note.len + block.pos) == this->tick) {
                    lane->instrument->stop(note.note);
                }
            }
        }
    }

    double sample = 0;
    
    for (auto& lane : this->lanes) {
        double instrument_sample = lane->instrument->render();
        sample += instrument_sample;
        for (auto& effect : lane->effects) {
            sample += effect->render(instrument_sample);
        }
    }
    
    // TODO Remove live_instruments
    for (auto& live_instrument : this->live_instruments) {
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
