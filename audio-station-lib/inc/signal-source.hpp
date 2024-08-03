#ifndef AUDIO_STATION_SIGNAL_SOURCE_HPP
#define AUDIO_STATION_SIGNAL_SOURCE_HPP

#include "audio-sample.hpp"

namespace audiostation {

    class SignalSource {
    public:
        virtual AudioSample render() = 0;
        virtual ~SignalSource() {};
    };
}

#endif // AUDIO_STATION_SIGNAL_SOURCE_HPP
