#include "audio-station.hpp"
#include "mixer.hpp"
#include "reverb.hpp"
#include "sequencer.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE;

void reverb_demo() {
    Synth synth;
    Reverb reverb({
        .size = 0.65,
        .level = 0.25
    });

    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 8 * bar,
        .blocks = { SequenceBlock() }
    });

    Mixer mixer({ 
        Track({ 
            .sequencer = &sequencer, 
            .instrument = &synth, 
            .effects = { &reverb }
        })
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(16);
    station.stop();
}
