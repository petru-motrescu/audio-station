#ifndef AUDIO_STATION_PROJECT_HPP
#define AUDIO_STATION_PROJECT_HPP

#include <memory>
#include <vector>
#include <unordered_map>
#include "audio-sample.hpp"
#include "audio-signal-source.hpp"
#include "effect.hpp"
#include "instrument.hpp"
#include "sequencer.hpp"
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

    struct ProjectConfig {
        std::vector<TrackLane*> lanes;
        std::vector<Sequencer*> sequencers;
    };

    class Project : public AudioSignalSource {
    public:
        Project();
        Project(ProjectConfig config);
        AudioSample render() override;
    
    private:
        ProjectConfig config;
        Tick tick;
    };
}

#endif // AUDIO_STATION_PROJECT_HPP