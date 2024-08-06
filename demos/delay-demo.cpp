#include "audio-station.hpp"
#include "delay.hpp"
#include "drum.hpp"
#include "mixer.hpp"
#include "sequencer.hpp"
#include "utils.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 3;

void delay_demo() {
    Sequencer sequencer({
        .loop_enabled = true,
        .loop_length = 8 * bar,
        .blocks = { SequenceBlock() }
    });

    Drum drum;
    
    Delay delay({
        .time = 250,
        .feedback = 0.8,
        .level = 0.75
    });

    Mixer mixer({ 
        Track({ 
            .sequencer = &sequencer, 
            .instrument = &drum,
            .effects = { &delay },
        }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep_for_seconds(8);
    station.stop();
}
