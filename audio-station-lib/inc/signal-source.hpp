#ifndef AUDIO_STATION_SIGNAL_SOURCE_HPP
#define AUDIO_STATION_SIGNAL_SOURCE_HPP

#include "note.hpp"

namespace audiostation {

    class SignalSource {
    public:
        virtual double render() = 0;
        virtual ~SignalSource() {};
    };
}

#endif // AUDIO_STATION_SIGNAL_SOURCE_HPP
