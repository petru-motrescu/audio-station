#include "audio-station.hpp"
#include "drum.hpp"
#include "utils.hpp"
using namespace audiostation;

void drum_demo() {    
    Drum drum({
        .opening_signal = { 
            .wave = Wave::Triangle, 
            .frequency = 120, 
            .amplitude = 0.5
        },
        .closing_signal = { 
            .wave = Wave::Sine, 
            .frequency = 40, 
            .amplitude = 0.6
        },
        .release_duration = 250,
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
