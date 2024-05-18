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
    run_wave_rendering_tests();
    run_audio_rendering_tests();
    run_synth_tests();
    std::cout << "✅ All tests done" << std::endl;
}

void run_synth_demo() {
    AudioStation station;
    station.init();
    station.play();
    
    Synth synth;
    synth.set_envelope({.atack = 30});
    station.add_synth(&synth);
    
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
    station.play();

    Oscillator oscillator;
    station.add_oscillator(&oscillator);
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
