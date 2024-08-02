#ifndef AUDIO_STATION_GENERATOR_HPP
#define AUDIO_STATION_GENERATOR_HPP

#include "note.hpp"

namespace audiostation {

    class Generator {
    public:
        virtual double render() = 0;
        virtual ~Generator() {};
    };
}

#endif // AUDIO_STATION_GENERATOR_HPP
