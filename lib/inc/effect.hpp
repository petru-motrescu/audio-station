#ifndef AUDIO_STATION_EFFECT_HPP
#define AUDIO_STATION_EFFECT_HPP

#include <vector>
#include "audio-sample.hpp"
#include "note.hpp"

namespace audiostation {

    class Effect {
    public:
        virtual AudioSample render(AudioSample sample) = 0;
        virtual ~Effect() {};
    };
}

#endif // AUDIO_STATION_EFFECT_HPP
