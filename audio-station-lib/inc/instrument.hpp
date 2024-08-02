#ifndef AUDIO_STATION_INSTRUMENT_HPP
#define AUDIO_STATION_INSTRUMENT_HPP

#include "note.hpp"
#include "player.hpp"

namespace audiostation {

    class Instrument : public Player {
    public:
        virtual double render() = 0;
        virtual ~Instrument() {};
    };
}

#endif // AUDIO_STATION_INSTRUMENT_HPP
