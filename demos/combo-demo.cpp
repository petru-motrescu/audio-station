#include "audio-station.hpp"
#include "combo.hpp"
#include "drum.hpp"
#include "mixer.hpp"
#include "noise.hpp"
#include "synth.hpp"
#include "utils.hpp"
using namespace audiostation;

void combo_demo() {
    Drum drum;
    Noise noise;
    Synth synth;
    Combo combo({ &drum, &noise, &synth });

    AudioStation station;
    station.init();
    station.play(&combo);

    for (int i = 0; i < 8; i++) {
        combo.trigger(Note::B1);
        sleep_for_millis(100);
        combo.release(Note::B1);
        sleep_for_millis(300);
    }

    station.stop();
}
