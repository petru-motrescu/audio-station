#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include <vector>
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
    run_renderer_tests();
    std::cout << "✅ All tests done" << std::endl;
}

void run_synth_demo() {
    AudioStation station;
    station.init();

    Synth synth;
    synth.set_envelope({ .atack = 20, .decay = 50, .sustain = 0.75, .release = 3000 });

    Track track { .synths = { &synth } };
    station.play(&track);
    
    std::vector<Note> notes = { Note::D3, Note::A3, Note::D4 };
    for (auto& note : notes) {
        synth.play_note(note);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        synth.stop_note(note);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    
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
