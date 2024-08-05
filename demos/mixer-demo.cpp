#include "audio-station.hpp"
#include "drum.hpp"
#include "mixer.hpp"
#include "noise.hpp"
#include "utils.hpp"
using namespace audiostation;

void mixer_demo() {
    Drum drum;
    Noise noise;
    Mixer mixer({ 
        Track({ .instrument = &drum }),
        Track({ .instrument = &noise }),
    });

    AudioStation station;
    station.init();
    station.play(&mixer);

    noise.trigger();
    for (int i = 0; i < 8; i++) {
        drum.trigger();
        sleep_for_millis(500);
    }

    station.stop();
}
