#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include "audio-station.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
#include "tests.hpp"
using namespace audiostation;

void run_tests() {
    std::cout << "🧪 Running tests" << std::endl;
    run_oscillator_tests();
    run_synth_tests();
    run_track_tests();
    run_wave_rendering_tests();
    std::cout << "✅ All tests done" << std::endl;
}

void run_synth_demo() {
    AudioStation station;
    station.init();

    Synth synth;
    synth.set_envelope({ .atack = 20, .decay = 100, .sustain = 0.75, .release = 100 });

    Track track { .synths = { &synth } };
    station.play(&track);
    
    for (auto& note : Notes::piano_notes) {
        synth.play_note(note);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        synth.stop_note(note);
    }
    
    station.stop();
}

void run_oscillator_demo() {
    AudioStation station;
    station.init();

    Oscillator oscillator;
    Track track;
    track.add_oscillator(&oscillator);
    station.play(&track);

    oscillator.play();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    oscillator.stop();

    station.stop();
}

int main() {
    run_tests();
    run_synth_demo();
    // run_oscillator_demo();
    return 0;
}
