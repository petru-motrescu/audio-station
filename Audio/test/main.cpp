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

constexpr unsigned bar = Config::SAMPLE_RATE / 2;
constexpr unsigned half = Config::SAMPLE_RATE / 4;
constexpr unsigned sixteenth = Config::SAMPLE_RATE / 16;

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

TrackLane build_kick_lane(BassDrum& kick) {
    std::vector<TrackNote> kick_notes = { 
        { .pos = 0 * bar }, 
        { .pos = 1 * bar },
        { .pos = 2 * bar },
        { .pos = 3 * bar },
    };

    TrackLane kick_lane = {
        .label = "Kick",
        .instrument = &kick,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = kick_notes },
            { .pos = 4 * bar * 1, .notes = kick_notes },
        }
    };

    return kick_lane;
}

TrackLane build_click_lane(BassDrum& click) {
    std::vector<TrackNote> click_notes = { 
        { .pos = 0 * bar + half }, 
        { .pos = 1 * bar + half },
        { .pos = 1 * bar + half + 1 * sixteenth }, 
        { .pos = 1 * bar + half + 2 * sixteenth },
        { .pos = 1 * bar + half + 3 * sixteenth },
        { .pos = 2 * bar + half },
        { .pos = 3 * bar + half },
        { .pos = 3 * bar + half + 1 * sixteenth }, 
        { .pos = 3 * bar + half + 2 * sixteenth },
        { .pos = 3 * bar + half + 3 * sixteenth },
    };
    
    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = click_notes },
            { .pos = 4 * bar * 1, .notes = click_notes },
        }
    };

    return click_lane;
}

TrackLane build_hihat_lane(BassDrum& hihat) {
    std::vector<TrackNote> hihat_notes = { 
        { .pos = 0 * bar + half }, 
        { .pos = 1 * bar + half },
        { .pos = 2 * bar + half },
        { .pos = 3 * bar + half },
    };

    TrackLane hihat_lane = {
        .label = "Hihat",
        .instrument = &hihat,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = hihat_notes },
            { .pos = 4 * bar * 1, .notes = hihat_notes },
        }
    };

    return hihat_lane;
}

TrackLane build_bass_lane(Synth& bass) {
    std::vector<TrackNote> bass_notes = {
        { .pos = 0 * bar, .note = Note::E1 },
        { .pos = 1 * bar, .note = Note::D1 },
        { .pos = 2 * bar, .note = Note::C1 },
        { .pos = 3 * bar, .note = Note::B0 },
    };

    TrackLane bass_lane = {
        .label = "Bass",
        .instrument = &bass,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = bass_notes },
            { .pos = 4 * bar * 1, .notes = bass_notes },
        }
    };

    return bass_lane;
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

    BassDrum hihat({
        .waveform = Waveform::Noise,
        .decay_millis = 150,
        .amplitude = 0.1,
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

    TrackLane kick_lane = build_kick_lane(kick);
    TrackLane click_lane = build_click_lane(click);
    TrackLane hihat_lane = build_hihat_lane(hihat);
    TrackLane bass_lane = build_bass_lane(bass);

    Track track { 
        .lanes = { &kick_lane, &click_lane, &hihat_lane, &bass_lane },
        .debug = true,
    };

    station.play(&track);
    sleep(5000);

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
    run_track_demo();
    // run_oscillator_demo();
    return 0;
}
