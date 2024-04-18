#ifndef AUDIO_STATION_HPP
#define AUDIO_STATION_HPP

#include <memory>

namespace audiostation {

    struct AudioStationImpl;

    struct AudioStation {
        AudioStation();
        ~AudioStation();

        void init();
        void play();
        void stop();

    private:
        std::unique_ptr<AudioStationImpl> impl;
    };
}

#endif // AUDIO_STATION_HPP
