#ifndef AUDIO_STATION_TRACK_HPP
#define AUDIO_STATION_TRACK_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include "effect.hpp"
#include "instrument.hpp"
#include "sequencer.hpp"
#include "signal-source.hpp"
#include "note.hpp"

namespace audiostation {

    using Bar = unsigned;
    using Tick = unsigned;

    struct TrackNote {
        Note note = Note::C4;
        Tick pos = 0;
        Tick len = 1;
    };

    struct TrackBlock {
        std::vector<TrackNote> notes;
        Tick pos = 0;
    };

    struct TrackLane {
        std::string label;
        Instrument* instrument;
        std::vector<Effect*> effects;
        std::vector<TrackBlock> blocks;
    };

    struct TrackConfig {
        std::vector<TrackLane*> lanes;
        std::vector<Instrument*> live_instruments;
        std::vector<Sequencer*> sequencers;
    };

    class Track : public SignalSource {
    public:
        Track();
        Track(TrackConfig config);
        void add_live_instrument(Instrument* instrument);
        double render() override;
    
    private:
        TrackConfig config;
        Tick tick;
    };
}

#endif // AUDIO_STATION_TRACK_HPP
