#ifndef AUDIO_STATION_INSTRUMENT_HPP
#define AUDIO_STATION_INSTRUMENT_HPP

#include "note.hpp"

namespace audiostation {

    class Instrument {
    public:
        virtual double render() = 0;
        virtual void play_note(Note note) = 0;
        virtual void stop_note(Note note) = 0;
        virtual ~Instrument() {};
    };
}

#endif // AUDIO_STATION_INSTRUMENT_HPP
