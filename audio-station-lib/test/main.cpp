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
#include "delay.hpp"
#include "drum.hpp"
#include "frequency.hpp"
#include "oscillator.hpp"
#include "synth.hpp"
#include "test-suite.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 2;
constexpr unsigned half = Config::SAMPLE_RATE / 4;

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

TrackLane build_kick_lane(Drum& kick) {
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

TrackLane build_click_lane(Drum& click, Delay& delay_1, Delay& delay_2, Delay& delay_3) {
    std::vector<TrackNote> click_notes = { 
        { .pos = 0 * bar + half }, 
        { .pos = 1 * bar + half },
        { .pos = 2 * bar + half },
        { .pos = 3 * bar + half },
    };
    
    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .effects = { &delay_1, &delay_2, &delay_3 },
        .blocks = {
            { .pos = 4 * bar * 0, .notes = click_notes },
            { .pos = 4 * bar * 1, .notes = click_notes },
        }
    };

    return click_lane;
}

TrackLane build_hihat_lane(Drum& hihat) {
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
        { .pos = 0 * bar, .len = 2 * bar, .note = Note::A1 },
        { .pos = 3 * bar, .len = half, .note = Note::D2 }
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

    Drum kick({
        .attack = { .wave = Wave::Triangle, .frequency = 150, .amplitude = 0.3 },
        .release = { .wave = Wave::Sine, .frequency = 30, .amplitude = 1.0 },
        .duration = 150,
    });

    Drum click({
        .attack = { .wave = Wave::Triangle, .frequency = 2000, .amplitude = 0.2 },
        .release = { .wave = Wave::Sine, .frequency = 2000, .amplitude = 0.1 },
        .duration = 100,
    });

    Drum hihat({
        .attack = { .wave = Wave::Noise, .amplitude = 0.1 },
        .release = { .wave = Wave::Noise, .amplitude = 0.1 },
        .duration = 150,
    });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.6,
        .envelope = {
            .atack_duration = 5, 
            .decay_duration = 20, 
            .sustain_level = 0.9, 
            .release_duration = 400
        }
    });

    Delay delay_1({ .time = 80, .level = 0.60 });
    Delay delay_2({ .time = 100, .level = 0.40 });
    Delay delay_3({ .time = 150, .level = 0.30 });

    TrackLane kick_lane = build_kick_lane(kick);
    TrackLane click_lane = build_click_lane(click, delay_1, delay_2, delay_3);
    TrackLane hihat_lane = build_hihat_lane(hihat);
    TrackLane bass_lane = build_bass_lane(bass);

    Track track { 
        .lanes = { 
            &kick_lane, &click_lane, &hihat_lane, &bass_lane
        }
    };

    station.play(&track);
    sleep(5000);

    station.stop();
}

void run_oscillator_demo() {
    Oscillator sine_oscillator(Wave::Sine);
    Oscillator triangle_oscillator(Wave::Triangle);
    Oscillator square_oscillator(Wave::Square);
    Oscillator noise_oscillator(Wave::Noise);
    
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

void run_delay_demo() {
    Drum drum;
    Delay delay({ 
        .time = 200,
        .feedback = 1.0,
        .level = 1.0
    });

    TrackLane lane = {
        .label = "Drum",
        .instrument = &drum,
        .effects = { &delay }
    };

    Track track { .lanes = { &lane } };

    AudioStation station;
    station.init();
    station.play(&track);

    for (int i = 0; i < 10; i++) {
        drum.play();
        sleep(3000);
    }
    
    station.stop();
}

int main() {
    TestSuite test_suite;
    test_suite.run_tests();
    // run_track_demo();
    // run_oscillator_demo();
    run_delay_demo();
    return 0;
}
