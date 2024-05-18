#ifndef AUDIO_STATION_HPP
#define AUDIO_STATION_HPP

#include <memory>
#include <vector>
#include "oscillator.hpp"
#include "synth.hpp"

namespace audiostation {

    struct AudioStationImpl;

    struct AudioStation {
        AudioStation();
        ~AudioStation();

        void init();
        void add_oscillator(audiostation::Oscillator* oscillator);
        void add_synth(audiostation::Synth* synth);
        void play();
        void stop();

    private:
        std::unique_ptr<AudioStationImpl> impl;
    };
}

#endif // AUDIO_STATION_HPP
