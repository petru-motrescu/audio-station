#ifndef AUDIO_STATION_SEQUENCER_HPP
#define AUDIO_STATION_SEQUENCER_HPP

#include <chrono>
#include <memory>
#include "config.hpp"
#include "generator.hpp"
#include "instrument.hpp"
#include "note.hpp"
#include "player.hpp"

namespace audiostation {

    struct SequenceStep {
        Note note;
        double level;
    };

    struct SequencerConfig {
        std::vector<Player*> outputs;

        std::vector<SequenceStep> steps = {
            { .note = Note::C4, .level = 1.0 },
            { .note = Note::C4, .level = 1.0 },
            { .note = Note::C4, .level = 1.0 },
            { .note = Note::C4, .level = 1.0 },
        };

        unsigned step_duration = 500; // TODO Use std::chrono::duration

        unsigned sample_rate = Config::SAMPLE_RATE;
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
        void tick();

    private:
        std::unique_ptr<SequencerImpl> impl;
    };
}

#endif // AUDIO_STATION_SEQUENCER_HPP
