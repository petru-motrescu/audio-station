#ifndef AUDIO_STATION_TRACK_HPP
#define AUDIO_STATION_TRACK_HPP

#include <memory>
#include <vector>
#include "instrument.hpp"

namespace audiostation {

    struct Track {
        void add_instrument(Instrument* instrument);
        double render();
    
        std::vector<Instrument*> instruments = std::vector<Instrument*>();
    };
}

#endif // AUDIO_STATION_TRACK_HPP
