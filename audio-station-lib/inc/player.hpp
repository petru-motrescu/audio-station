#ifndef AUDIO_STATION_PLAYER_HPP
#define AUDIO_STATION_PLAYER_HPP

#include "note.hpp"

namespace audiostation {

    class Player {
    public:
        virtual void play(Note note) = 0;
        virtual void stop(Note note) = 0;
        virtual ~Player() {};
    };
}

#endif // AUDIO_STATION_PLAYER_HPP
