#ifndef AUDIO_STATION_HPP
#define AUDIO_STATION_HPP

#include <memory>
#include <vector>
#include "audio-signal.hpp"

namespace audiostation {

    struct AudioStationImpl;

    struct AudioStation {
        AudioStation();
        ~AudioStation();

        void init();
        void add(audiostation::AudioSignal signal);
        void add(std::vector<audiostation::AudioSignal> signals);
        void play();
        void stop();

    private:
        std::unique_ptr<AudioStationImpl> impl;
    };
}

#endif // AUDIO_STATION_HPP
