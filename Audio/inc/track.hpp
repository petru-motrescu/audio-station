#ifndef AUDIO_STATION_TRACK_HPP
#define AUDIO_STATION_TRACK_HPP

#include <memory>
#include <vector>
#include "bass-drum.hpp"
#include "oscillator.hpp"
#include "synth.hpp"

namespace audiostation {

    struct Track {
        void add_bass_drum(BassDrum* bass_drum);
        void add_oscillator(Oscillator* oscillator);
        void add_synth(Synth* synth);
        double render();
    
        std::vector<BassDrum*> bass_drums = std::vector<BassDrum*>();
        std::vector<Oscillator*> oscillators = std::vector<Oscillator*>();
        std::vector<Synth*> synths = std::vector<Synth*>();
    };
}

#endif // AUDIO_STATION_TRACK_HPP
