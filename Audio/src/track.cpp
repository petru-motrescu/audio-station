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

void audiostation::Track::add_live_instrument(Instrument* instrument) {
    this->live_instruments.push_back(instrument);
}

double audiostation::Track::render() {
    for (auto& lane : this->lanes) {
        for (auto& block : lane->blocks) {
            for (auto& note : block.notes) {
                if ((note.start_tick + block.offset) == this->tick) {
                    if (debug) {
                        std::cout 
                            << "Playing " 
                            << lane->label 
                            << "(" 
                            << Notes::to_string(note.note) 
                            << ") @ " 
                            << this->tick << std::endl;
                    }
                    lane->instrument->play_note(note.note);
                }
                if ((note.start_tick + note.hold_ticks + block.offset) == this->tick) {
                    if (debug) {
                        std::cout 
                            << "Stopping " 
                            << lane->label 
                            << "(" 
                            << Notes::to_string(note.note) 
                            << ") @ " 
                            << this->tick << std::endl;
                    }
                    lane->instrument->stop_note(note.note);
                }
            }
        }
    }

    double sample = 0;
    
    for (auto& lane : this->lanes) {
        sample += lane->instrument->render();
    }
    
    for (auto& live_instrument : this->live_instruments) {
        sample += live_instrument->render();
    }

    this->tick++;

    return sample;
}
