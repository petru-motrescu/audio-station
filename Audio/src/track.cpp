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
                if ((note.bar + block.bar) * this->milliticks_per_bar == this->millitick) {
                    if (debug) {
                        std::cout 
                            << "Playing " 
                            << lane->label 
                            << "(" 
                            << Notes::to_string(note.note) 
                            << ") @ " 
                            << this->millitick << std::endl;
                    }
                    lane->instrument->play_note(note.note);
                }
                if ((note.bar + note.bar + block.bar) * this->milliticks_per_bar == this->millitick) {
                    if (debug) {
                        std::cout 
                            << "Stopping " 
                            << lane->label 
                            << "(" 
                            << Notes::to_string(note.note) 
                            << ") @ " 
                            << this->millitick << std::endl;
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

    this->millitick += 1000;

    return sample;
}
