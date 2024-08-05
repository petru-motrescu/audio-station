#include "audio-station.hpp"
#include "drum.hpp"
#include "utils.hpp"
using namespace audiostation;

void drum_demo() {    
    Drum drum({
        .attack = { 
            .wave = Wave::Triangle, 
            .frequency = 200, 
            .amplitude = 0.4
        },
        .release = { 
            .wave = Wave::Sine, 
            .frequency = 40, 
            .amplitude = 0.3
        },
        .duration = 300,
    });

    AudioStation station;
    station.init();
    station.play(&drum);

    for (int i = 0; i < 8; i++) {
        sleep_for_millis(500);
        drum.trigger();
    }
    
    station.stop();
}
