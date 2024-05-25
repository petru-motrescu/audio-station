#ifndef AUDIO_STATION_TRACK_HPP
#define AUDIO_STATION_TRACK_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include "instrument.hpp"
#include "note.hpp"

namespace audiostation {

    struct TrackNote {
        Note note = Note::C4;
        unsigned start_tick = 0;
        unsigned hold_ticks = 1;
    };

    struct TrackBar {
        std::vector<TrackNote> notes;
        unsigned offset = 0;
    };

    struct TrackLane {
        std::string label;
        Instrument* instrument;
        std::vector<TrackBar> bars;
    };

    struct Track {
        void add_live_instrument(Instrument* instrument);
        double render();
        std::vector<TrackLane*> lanes;
        std::vector<Instrument*> live_instruments;
        unsigned tick;
        bool debug;
    };
}

#endif // AUDIO_STATION_TRACK_HPP
