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

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

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

void run_track_demo() {
    AudioStation station;
    station.init();

    Synth synth;
    synth.set_envelope({
        .atack_millis = 5, 
        .decay_millis = 20, 
        .sustain_level = 0.8, 
        .release_millis = 300
    });

    BassDrum bass_drum({
        .waveform = Waveform::Sine,
        .atack_frequency = 120,
        .decay_frequency = 30,
        .decay_millis = 150,
        .amplitude = 0.5,
    });

    BassDrum click_drum({
        .waveform = Waveform::Sine,
        .atack_frequency = 2000,
        .decay_frequency = 2000,
        .decay_millis = 100,
        .amplitude = 0.2,
    });

    Track track { 
        .bass_drums = { &bass_drum, &click_drum }, 
        .synths = { &synth }
    };

    station.play(&track);

    for (int i = 0; i < 16; i++) {
        bass_drum.play();
        sleep(5);
        synth.play_note(Note::E1);
        sleep(20);
        synth.stop_note(Note::E1);
        sleep(250);
        click_drum.play();
        sleep(200);
    }

    station.stop();
}

int main() {
    // run_tests();
    // run_synth_demo();
    // run_oscillator_demo();
    // run_bass_drum_demo();
    run_track_demo();
    return 0;
}
