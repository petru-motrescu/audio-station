#ifndef AUDIO_STATION_PLAYABLE_HPP
#define AUDIO_STATION_PLAYABLE_HPP

#include "note.hpp"

namespace audiostation {

    class Playable {
    public:
        virtual void trigger(Note note) = 0;
        virtual void release(Note note) = 0;
        virtual ~Playable() {};
    };
}

#endif // AUDIO_STATION_PLAYABLE_HPP
