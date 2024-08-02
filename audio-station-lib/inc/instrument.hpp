#ifndef AUDIO_STATION_INSTRUMENT_HPP
#define AUDIO_STATION_INSTRUMENT_HPP

#include "playable.hpp"
#include "signal-source.hpp"

namespace audiostation {

    class Instrument : public Playable, public SignalSource {
    public:
        virtual ~Instrument() {};
    };
}

#endif // AUDIO_STATION_INSTRUMENT_HPP
