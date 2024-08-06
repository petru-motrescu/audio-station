#include "audio-station.hpp"
#include "mixer.hpp"
#include "sequencer.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 3;
constexpr unsigned half = bar / 2;

void sequencer_demo() {
    std::vector<SequenceNote> notes_1 = { 
        { .note = Note::GA2, .offset = 0 * bar, .length = half },
        { .note = Note::DE3, .offset = 1 * bar, .length = half  },
        { .note = Note::GA2, .offset = 4 * bar, .length = half  },
        { .note = Note::DE3, .offset = 5 * bar, .length = half  },
    };

    std::vector<SequenceNote> notes_2 = { 
        { .note = Note::AB2, .offset = 0 * bar, .length = half  },
        { .note = Note::DE3, .offset = 1 * bar, .length = half  },
        { .note = Note::AB2, .offset = 4 * bar, .length = half  },
        { .note = Note::DE3, .offset = 5 * bar, .length = half  },
    };

    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 16 * bar,
        .blocks = {
            { .offset = 0 * 8 * bar, .notes = notes_1 },
            { .offset = 1 * 8 * bar, .notes = notes_2 }
        }
    });

    Synth synth;
    Mixer mixer({ 
        Track({ .sequencer = &sequencer, .instrument = &synth }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(8);
    station.stop();
}
