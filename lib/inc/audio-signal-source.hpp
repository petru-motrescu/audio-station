#ifndef AUDIO_STATION_AUDIO_SIGNAL_SOURCE_HPP
#define AUDIO_STATION_AUDIO_SIGNAL_SOURCE_HPP

#include "audio-sample.hpp"

namespace audiostation {

    class AudioSignalSource {
    public:
        virtual AudioSample render() = 0;
        virtual ~AudioSignalSource() {};
    };
}

#endif // AUDIO_STATION_AUDIO_SIGNAL_SOURCE_HPP
