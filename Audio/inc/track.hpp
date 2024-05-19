#ifndef AUDIO_STATION_TRACK_HPP
#define AUDIO_STATION_TRACK_HPP

#include <memory>
#include <vector>
#include "oscillator.hpp"
#include "synth.hpp"

namespace audiostation {

    struct Track {
        void add_oscillator(Oscillator* oscillator);
        void add_synth(Synth* synth);
        double render();
    
        std::vector<Oscillator*> oscillators = std::vector<Oscillator*>();
        std::vector<Synth*> synths = std::vector<Synth*>();
    };
}

#endif // AUDIO_STATION_TRACK_HPP
