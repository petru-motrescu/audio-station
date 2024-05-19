#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include <vector>
#include "audio-station.hpp"
#include "bass-drum.hpp"
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
    synth.set_envelope({ 
        .atack_millis = 20, 
        .decay_millis = 50, 
        .sustain_level = 0.75, 
        .release_millis = 3000
    });

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

void run_bass_drum_demo() {
    AudioStation station;
    station.init();

    BassDrum bass_drum;
    Track track { .bass_drums = { &bass_drum } };
    station.play(&track);

    while (true) {
        bass_drum.play();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    station.stop();
}


int main() {
    // run_tests();
    // run_synth_demo();
    // run_oscillator_demo();
    run_bass_drum_demo();
    return 0;
}
