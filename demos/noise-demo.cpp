#include "audio-station.hpp"
#include "noise.hpp"
#include "utils.hpp"
using namespace audiostation;

void noise_demo() {    
    Noise noise({ .amplitude = 0.1 });
    AudioStation station;
    station.init();
    station.play(&noise);
    noise.trigger();
    sleep_for_seconds(2);
    station.stop();
}