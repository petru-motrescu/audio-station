#ifndef AUDIO_STATION_MIXER_HPP
#define AUDIO_STATION_MIXER_HPP

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
        Sequencer* sequencer;
        Instrument* instrument;
        std::vector<Effect*> effects;
    };

    class Mixer : public AudioSignalSource {
    public:
        Mixer();
        Mixer(std::vector<Track> tracks);
        AudioSample render() override;
    
    private:
        std::vector<Track> tracks;
        Tick tick;
    };
}

#endif // AUDIO_STATION_MIXER_HPP
