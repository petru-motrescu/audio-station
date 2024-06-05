#ifndef AUDIO_STATION_EFFECT_HPP
#define AUDIO_STATION_EFFECT_HPP

#include <vector>
#include "note.hpp"

namespace audiostation {

    struct Effect {
        virtual double render(double sample) = 0;
    };
}

#endif // AUDIO_STATION_EFFECT_HPP
