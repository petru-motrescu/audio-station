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
#include "tick.hpp"

namespace audiostation {

    struct Track {
        std::string label;
        Sequencer* sequencer;
        Instrument* instrument;
        std::vector<Effect*> effects;
    };

    struct ProjectConfig {
        std::vector<Track*> tracks;
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
