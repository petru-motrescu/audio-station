#ifndef AUDIO_STATION_SEQUENCER_HPP
#define AUDIO_STATION_SEQUENCER_HPP

#include <chrono>
#include <memory>
#include "config.hpp"
#include "note.hpp"
#include "playable.hpp"
#include "tick.hpp"

namespace audiostation {

    struct SequenceNote {
        Note note = Note::C4;
        Tick offset = 0;
        Tick length = 1;
        double level = 1.0;
    };

    struct SequenceBlock {
        std::vector<SequenceNote> notes = {
            { .note = Note::C4 },
            { .note = Note::A4, .offset = Config::SAMPLE_RATE / 2 },
        };

        Tick offset = 0;
    };

    struct SequencerConfig {
        std::vector<SequenceBlock> blocks = { SequenceBlock() };
        bool loop_enabled = true;
        Tick loop_length = Config::SAMPLE_RATE;
        Tick sample_rate = Config::SAMPLE_RATE;
    };

    struct SequencerImpl;

    class Sequencer {
    public:
        Sequencer();
        Sequencer(SequencerConfig config);
        Sequencer(const Sequencer& other);
        Sequencer(Sequencer&& other);
        Sequencer& operator=(Sequencer&& other);
        ~Sequencer();

        void trigger();
        bool is_live() const;
        void render(Playable& output);

    private:
        std::unique_ptr<SequencerImpl> impl;
    };
}

#endif // AUDIO_STATION_SEQUENCER_HPP
