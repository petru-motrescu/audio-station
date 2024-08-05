#include "audio-station.hpp"
#include "oscillator.hpp"
#include "utils.hpp"
using namespace audiostation;

void oscillator_demo() {    
    Oscillator oscillator({
        .wave = Wave::Sine,
        .frequency = Frequency::C4,
        .amplitude = 0.25,
    });

    AudioStation station;
    station.init();
    station.play(&oscillator);
    oscillator.trigger();
    sleep_for_seconds(2);
    station.stop();
}
