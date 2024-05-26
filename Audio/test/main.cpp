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
            .release_millis = 400
        }
    });

    auto bar = Config::SAMPLE_RATE / 2;
    auto half = Config::SAMPLE_RATE / 4;

    std::vector<TrackNote> kick_notes = { 
        { .pos = 0 * bar }, 
        { .pos = 1 * bar },
        { .pos = 2 * bar },
        { .pos = 3 * bar },
    };

    std::vector<TrackNote> click_notes = { 
        { .pos = 0 * bar + half }, 
        { .pos = 1 * bar + half },
        { .pos = 2 * bar + half },
        { .pos = 3 * bar + half },
    };

    std::vector<TrackNote> bass_notes = {
        { .pos = 0 * bar, .note = Note::E1 },
        { .pos = 1 * bar, .note = Note::D1 },
        { .pos = 2 * bar, .note = Note::C1 },
        { .pos = 3 * bar, .note = Note::B0 },
    };

    TrackLane kick_lane = {
        .label = "Kick",
        .instrument = &kick,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = kick_notes },
            { .pos = 4 * bar * 1, .notes = kick_notes },
            { .pos = 4 * bar * 2, .notes = kick_notes },
            { .pos = 4 * bar * 3, .notes = kick_notes },
        }
    };

    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = click_notes },
            { .pos = 4 * bar * 1, .notes = click_notes },
            { .pos = 4 * bar * 2, .notes = click_notes },
            { .pos = 4 * bar * 3, .notes = click_notes },
        }
    };

    TrackLane bass_lane = {
        .label = "Bass",
        .instrument = &bass,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = bass_notes },
            { .pos = 4 * bar * 1, .notes = bass_notes },
            { .pos = 4 * bar * 2, .notes = bass_notes },
            { .pos = 4 * bar * 3, .notes = bass_notes },
        }
    };

    Track track { 
        .lanes = { 
            &kick_lane,
            &click_lane,
            &bass_lane,
        },
        .debug = true,
    };

    station.play(&track);
    sleep(9000);

    station.stop();
}

void run_oscillator_demo() {
    Oscillator sine_oscillator(Waveform::Sine);
    Oscillator triangle_oscillator(Waveform::Triangle);
    Oscillator square_oscillator(Waveform::Square);
    Oscillator noise_oscillator(Waveform::Noise);
    
    Track track { 
        .live_instruments = { 
            &sine_oscillator, 
            &triangle_oscillator, 
            &square_oscillator,
            &noise_oscillator,
        }
    };

    AudioStation station;
    station.init();
    station.play(&track);
    
    for (auto& oscilator : track.live_instruments) {
        oscilator->play_note(Note::C3);
        sleep(2000);
        oscilator->stop_note(Note::C3);
    }

    station.stop();
}

int main() {
    run_tests();
    // run_track_demo();
    run_oscillator_demo();
    return 0;
}
