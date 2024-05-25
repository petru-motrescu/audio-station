#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include <vector>
#include <limits>
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

void run_track_demo() {
    AudioStation station;
    station.init();

    BassDrum kick({
        .waveform = Waveform::Sine,
        .atack_frequency = 120,
        .decay_frequency = 30,
        .decay_millis = 150,
        .amplitude = 0.5,
    });

    BassDrum click({
        .waveform = Waveform::Sine,
        .atack_frequency = 2000,
        .decay_frequency = 2000,
        .decay_millis = 100,
        .amplitude = 0.2,
    });

    Synth bass({
        .waveform = Waveform::Triangle,
        .amplitude = 0.6,
        .envelope = {
            .atack_millis = 5, 
            .decay_millis = 20, 
            .sustain_level = 0.9, 
            .release_millis = 500
        }
    });

    std::vector<TrackNote> kick_notes = { { .bar = 0 }, { .bar = 4 }, { .bar = 8 }, { .bar = 12 } };
    std::vector<TrackNote> click_notes = { { .bar = 2 }, { .bar = 6 }, { .bar = 10 }, { .bar = 14 } };

    std::vector<TrackNote> bass_notes_1 = {
        { .note = Note::E1, .bar =  0 },
        { .note = Note::E1, .bar =  4 },
        { .note = Note::E1, .bar =  8 },
        { .note = Note::G1, .bar = 12 },
    };

    std::vector<TrackNote> bass_notes_2 = {
        { .note = Note::B1, .bar =  0 },
        { .note = Note::A1, .bar =  4 },
        { .note = Note::G1, .bar =  8 },
        { .note = Note::E1, .bar = 12 },
    };

    TrackLane kick_lane = {
        .label = "Kick",
        .instrument = &kick,
        .blocks = {
            { .bar =  0, .notes = kick_notes },
            { .bar = 16, .notes = kick_notes },
            { .bar = 32, .notes = kick_notes },
            { .bar = 48, .notes = kick_notes },
        }
    };

    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .blocks = {
            { .bar =  0, .notes = click_notes },
            { .bar = 16, .notes = click_notes },
            { .bar = 32, .notes = click_notes },
            { .bar = 48, .notes = click_notes },
        }
    };

    TrackLane bass_lane = {
        .label = "Bass",
        .instrument = &bass,
        .blocks = {
            { .bar =  0, .notes = bass_notes_1 },
            { .bar = 16, .notes = bass_notes_1 },
            { .bar = 32, .notes = bass_notes_1 },
            { .bar = 48, .notes = bass_notes_2 },
        }
    };

    Track track { 
        .lanes = { &kick_lane, &click_lane, &bass_lane },
        .milliticks_per_bar = Config::SAMPLE_RATE * 1000 / 8,
        .debug = true,
    };

    station.play(&track);
    sleep(9000);

    station.stop();
}

int main() {
    std::cout << std::numeric_limits<unsigned long>::max() << std::endl;
    run_tests();
    run_track_demo();
    return 0;
}
