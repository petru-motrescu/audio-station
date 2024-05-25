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

    auto ticks = Config::SAMPLE_RATE / 8;

    std::vector<TrackNote> kick_notes = {
        { .start_tick =  0 * ticks },
        { .start_tick =  4 * ticks },
        { .start_tick =  8 * ticks },
        { .start_tick = 12 * ticks },
    };

    std::vector<TrackNote> click_notes = {
        { .start_tick = ( 0 + 2) * ticks },
        { .start_tick = ( 4 + 2) * ticks },
        { .start_tick = ( 8 + 2) * ticks },
        { .start_tick = (12 + 2) * ticks },
    };

    std::vector<TrackNote> bass_notes_1 = {
        { .note = Note::E1, .start_tick =  0 * ticks },
        { .note = Note::E1, .start_tick =  4 * ticks },
        { .note = Note::E1, .start_tick =  8 * ticks },
        { .note = Note::G1, .start_tick = 12 * ticks },
    };

    std::vector<TrackNote> bass_notes_2 = {
        { .note = Note::B1, .start_tick =  0 * ticks },
        { .note = Note::A1, .start_tick =  4 * ticks },
        { .note = Note::G1, .start_tick =  8 * ticks },
        { .note = Note::E1, .start_tick = 12 * ticks },
    };

    TrackLane kick_lane = {
        .label = "Kick",
        .instrument = &kick,
        .bars = {
            { .offset =  0 * ticks, .notes = kick_notes },
            { .offset = 16 * ticks, .notes = kick_notes },
            { .offset = 32 * ticks, .notes = kick_notes },
            { .offset = 48 * ticks, .notes = kick_notes },
        }
    };

    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .bars = {
            { .offset =  0 * ticks, .notes = click_notes },
            { .offset = 16 * ticks, .notes = click_notes },
            { .offset = 32 * ticks, .notes = click_notes },
            { .offset = 48 * ticks, .notes = click_notes },
        }
    };

    TrackLane bass_lane = {
        .label = "Bass",
        .instrument = &bass,
        .bars = {
            { .offset =  0 * ticks, .notes = bass_notes_1 },
            { .offset = 16 * ticks, .notes = bass_notes_1 },
            { .offset = 32 * ticks, .notes = bass_notes_1 },
            { .offset = 48 * ticks, .notes = bass_notes_2 },
        }
    };

    Track track { 
        .lanes = { &kick_lane, &click_lane, &bass_lane },
        .debug = true,
    };

    station.play(&track);
    sleep(9000);

    station.stop();
}

int main() {
    run_tests();
    run_track_demo();
    return 0;
}
