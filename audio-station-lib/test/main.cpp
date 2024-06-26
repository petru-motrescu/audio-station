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
#include "reverb.hpp"
#include "synth.hpp"
#include "test-suite.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 2;
constexpr unsigned half = Config::SAMPLE_RATE / 4;
constexpr unsigned quart = Config::SAMPLE_RATE / 8; // 5512,5
constexpr unsigned eighth = Config::SAMPLE_RATE / 16;

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

TrackLane build_kick_lane(Drum& kick) {
    std::vector<TrackNote> kick_notes = { 
        { .pos = 0 * bar }, 
        { .pos = 2 * bar + half },
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

    return kick_lane;
}

TrackLane build_click_lane(Drum& click, Delay& delay) {
    std::vector<TrackNote> click_notes = { 
        { .pos = 2 * bar }
    };
    
    TrackLane click_lane = {
        .label = "Click",
        .instrument = &click,
        .effects = { &delay },
        .blocks = {
            { .pos = 4 * bar * 2, .notes = click_notes },
            { .pos = 4 * bar * 3, .notes = click_notes },
        }
    };

    return click_lane;
}

TrackLane build_hihat_lane(Drum& hihat) {
    std::vector<TrackNote> hihat_notes = { 
        { .pos = 1 * bar + half },
        { .pos = 3 * bar + half },
    };

    TrackLane hihat_lane = {
        .label = "Hihat",
        .instrument = &hihat,
        .blocks = {
            { .pos = 4 * bar * 2, .notes = hihat_notes },
            { .pos = 4 * bar * 3, .notes = hihat_notes },
        }
    };

    return hihat_lane;
}

TrackLane build_bass_lane(Synth& bass) {
    std::vector<TrackNote> bass_notes = {
        { .pos = 2 * bar + half, .len = 3 * quart, .note = Note::C2 },
        { .pos = 3 * bar + 1 * quart, .len = 1 * quart, .note = Note::A1 },
        { .pos = 3 * bar + 2 * quart, .len = 1 * eighth, .note = Note::A1 },
        { .pos = 3 * bar + 3 * quart, .len = 1 * eighth, .note = Note::A1 },
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

    return bass_lane;
}

TrackLane build_lead_lane(Synth& lead, Reverb& reverb) {
    std::vector<TrackNote> notes = {
        { .pos = 0 * bar, .len = 1 * eighth, .note = Note::B3 },
    };

    TrackLane lane = {
        .label = "Lead",
        .instrument = &lead,
        .effects = { &reverb },
        .blocks = {
            { .pos = 4 * bar * 0, .notes = notes }
        }
    };

    return lane;
}

void run_track_demo() {
    AudioStation station;
    station.init();

    Drum kick({
        .attack = { .wave = Wave::Triangle, .frequency = Frequency::A2, .amplitude = 0.5 },
        .release = { .wave = Wave::Sine, .frequency = Frequency::B0, .amplitude = 1.0 },
        .duration = 200,
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
        .amplitude = 0.4,
        .envelope = {
            .atack_duration = 5, 
            .decay_duration = 20, 
            .sustain_level = 0.9, 
            .release_duration = 400
        }
    });

    Synth lead({
        .wave = Wave::Sine,
        .amplitude = 0.2,
        .envelope = {
            .atack_duration = 5, 
            .decay_duration = 5, 
            .sustain_level = 1.0, 
            .release_duration = 40
        }
    });

    Delay delay({ .time = 80, .level = 0.6, .feedback = 0.75 });
    Reverb reverb;

    TrackLane kick_lane = build_kick_lane(kick);
    TrackLane click_lane = build_click_lane(click, delay);
    TrackLane hihat_lane = build_hihat_lane(hihat);
    TrackLane bass_lane = build_bass_lane(bass);
    TrackLane lead_lane = build_lead_lane(lead, reverb);

    Track track { .lanes = { &kick_lane, &click_lane, &hihat_lane, &bass_lane, &lead_lane } };

    station.play(&track);
    sleep(9000);

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
        .time = 250,
        .feedback = 0.99,
        .level = 0.75
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

    for (int i = 0; i < 5; i++) {
        drum.play();
        sleep(5000);
    }
    
    station.stop();
}

void run_reverb_demo() {
    unsigned note_duration = (unsigned) 16 * M_PI;

    Synth synth_1({
        .amplitude = 0.4,
        .envelope = {
            .atack_duration = 0, 
            .decay_duration = 0, 
            .sustain_level = 1.0,
            .release_duration = note_duration
        }
    });

    Synth synth_2({
        .amplitude = 0.4,
        .envelope = {
            .atack_duration = 0, 
            .decay_duration = 0, 
            .sustain_level = 1.0,
            .release_duration = note_duration
        }
    });

    Reverb reverb;
    TrackLane lane_1 = { .label = "1", .instrument = &synth_1 };
    TrackLane lane_2 = { .label = "2", .instrument = &synth_2, .effects = { &reverb } };
    Track track { .lanes = { &lane_1, &lane_2 } };
    AudioStation station;
    station.init();
    station.play(&track);
    
    for (int i = 0; i < 4; i++) {
        synth_1.play_note(Note::A3);
        sleep(note_duration);
        synth_1.stop_note(Note::A3);
        sleep(1000);

        synth_2.play_note(Note::A3);
        sleep(note_duration);
        synth_2.stop_note(Note::A3);
        sleep(15000);
    }
    
    station.stop();
}

int main() {
    // TestSuite test_suite;
    // test_suite.run_tests();
    run_track_demo();
    // run_oscillator_demo();
    // run_delay_demo();
    // run_reverb_demo();
    return 0;
}
