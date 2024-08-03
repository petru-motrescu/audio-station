#ifndef AUDIO_STATION_HPP
#define AUDIO_STATION_HPP

#include <memory>
#include <vector>
#include "audio-signal-source.hpp"

namespace audiostation {

    struct AudioStationImpl;

    class AudioStation {
    public:
        AudioStation();
        ~AudioStation();

        void init();
        void play(AudioSignalSource* source);
        void stop();

    private:
        std::unique_ptr<AudioStationImpl> impl;
    };
}

#endif // AUDIO_STATION_HPP
