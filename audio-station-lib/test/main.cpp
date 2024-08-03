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
#include "noise.hpp"
#include "oscillator.hpp"
#include "project.hpp"
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

Track build_kick_track(Drum& kick) {
    std::vector<TrackNote> kick_notes = { 
        { .pos = 0 * bar }, 
        { .pos = 2 * bar + half },
    };

    Track kick_track = {
        .label = "Kick",
        .instrument = &kick,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = kick_notes },
            { .pos = 4 * bar * 1, .notes = kick_notes },
            { .pos = 4 * bar * 2, .notes = kick_notes },
            { .pos = 4 * bar * 3, .notes = kick_notes },
        }
    };

    return kick_track;
}

Track build_click_track(Drum& click, Delay& delay) {
    std::vector<TrackNote> click_notes = { 
        { .pos = 2 * bar }
    };
    
    Track click_track = {
        .label = "Click",
        .instrument = &click,
        .effects = { &delay },
        .blocks = {
            { .pos = 4 * bar * 2, .notes = click_notes },
            { .pos = 4 * bar * 3, .notes = click_notes },
        }
    };

    return click_track;
}

Track build_hihat_track(Noise& hihat) {
    std::vector<TrackNote> hihat_notes = { 
        { .pos = 1 * bar + half, .len = 1 * eighth },
        { .pos = 3 * bar + half, .len = 1 * eighth },
    };

    Track hihat_track = {
        .label = "Hihat",
        .instrument = &hihat,
        .blocks = {
            { .pos = 4 * bar * 2, .notes = hihat_notes },
            { .pos = 4 * bar * 3, .notes = hihat_notes },
        }
    };

    return hihat_track;
}

Track build_bass_track(Synth& bass) {
    std::vector<TrackNote> bass_notes = {
        { .pos = 2 * bar + half, .len = 3 * quart, .note = Note::C2 },
        { .pos = 3 * bar + 1 * quart, .len = 1 * quart, .note = Note::A1 },
        { .pos = 3 * bar + 2 * quart, .len = 1 * eighth, .note = Note::A1 },
        { .pos = 3 * bar + 3 * quart, .len = 1 * eighth, .note = Note::A1 },
    };

    Track bass_track = {
        .label = "Bass",
        .instrument = &bass,
        .blocks = {
            { .pos = 4 * bar * 0, .notes = bass_notes },
            { .pos = 4 * bar * 1, .notes = bass_notes },
            { .pos = 4 * bar * 2, .notes = bass_notes },
            { .pos = 4 * bar * 3, .notes = bass_notes },
        }
    };

    return bass_track;
}

Track build_lead_track(Synth& lead, Reverb& reverb) {
    std::vector<TrackNote> notes = {
        { .pos = 0 * bar, .len = 1 * eighth, .note = Note::B3 },
    };

    Track track = {
        .label = "Lead",
        .instrument = &lead,
        .effects = { &reverb },
        .blocks = {
            { .pos = 4 * bar * 0, .notes = notes }
        }
    };

    return track;
}

void run_song_demo() {
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

    Noise hihat({ .amplitude = 0.1 });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.4,
        .harmonics = 0,
        .envelope = {
            .attack_duration = 5, 
            .decay_duration = 20, 
            .sustain_level = 0.9, 
            .release_duration = 400
        }
    });

    Synth lead({
        .wave = Wave::Sine,
        .amplitude = 0.2,
        .harmonics = 0,
        .envelope = {
            .attack_duration = 5, 
            .decay_duration = 5, 
            .sustain_level = 1.0, 
            .release_duration = 40
        }
    });

    Delay delay({ .time = 80, .level = 0.6, .feedback = 0.75 });
    Reverb reverb;

    Track kick_track = build_kick_track(kick);
    Track click_track = build_click_track(click, delay);
    Track hihat_track = build_hihat_track(hihat);
    Track bass_track = build_bass_track(bass);
    Track lead_track = build_lead_track(lead, reverb);

    Project project({ .tracks = { &kick_track, &click_track, &hihat_track, &bass_track, &lead_track } });

    station.play(&project);
    sleep(9000);

    station.stop();
}

void run_noise_demo() {
    AudioStation station;
    station.init();

    Noise noise({});
    station.play(&noise);

    noise.trigger();
    sleep(2000);
    noise.release();
    
    station.stop();
}

void run_oscillator_demo() {
    std::vector<Oscillator> oscillators {
        Oscillator({.wave = Wave::Sine, .amplitude = 0.5}),
        Oscillator({.wave = Wave::Triangle, .amplitude = 0.4}),
        Oscillator({.wave = Wave::Square, .amplitude = 0.08}),
    };
    
    AudioStation station;
    station.init();
    
    for (auto& oscilator : oscillators) {
        station.play(&oscilator);
        oscilator.trigger(Note::C3);
        sleep(2000);
        oscilator.release(Note::C3);
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

    Track track = {
        .label = "Drum",
        .instrument = &drum,
        .effects = { &delay }
    };

    Project project({ .tracks = { &track } });

    AudioStation station;
    station.init();
    station.play(&project);

    for (int i = 0; i < 5; i++) {
        drum.trigger();
        sleep(5000);
    }
    
    station.stop();
}

void run_reverb_demo() {
    unsigned note_duration = (unsigned) 16 * M_PI;

    Synth synth_1({
        .amplitude = 0.4,
        .envelope = {
            .attack_duration = 0, 
            .decay_duration = 0, 
            .sustain_level = 1.0,
            .release_duration = note_duration
        }
    });

    Synth synth_2({
        .amplitude = 0.4,
        .envelope = {
            .attack_duration = 0, 
            .decay_duration = 0, 
            .sustain_level = 1.0,
            .release_duration = note_duration
        }
    });

    Reverb reverb;
    Track track_1 = { .label = "1", .instrument = &synth_1 };
    Track track_2 = { .label = "2", .instrument = &synth_2, .effects = { &reverb } };
    Project project({ .tracks = { &track_1, &track_2 } });
    AudioStation station;
    station.init();
    station.play(&project);
    
    for (int i = 0; i < 4; i++) {
        synth_1.trigger(Note::A3);
        sleep(note_duration);
        synth_1.release(Note::A3);
        sleep(1000);

        synth_2.trigger(Note::A3);
        sleep(note_duration);
        synth_2.release(Note::A3);
        sleep(15000);
    }
    
    station.stop();
}

void run_sequencer_demo() {
    Drum drum;
    Sequencer sequencer;
    Track track = { .sequencer = &sequencer, .instrument = &drum };
    Project project({ .tracks = { &track }});

    AudioStation station;
    station.init();
    station.play(&project);
    sleep(5000);
    station.stop();
}

int main() {
    TestSuite test_suite;
    test_suite.run_tests();
    // run_song_demo();
    // run_noise_demo();
    // run_oscillator_demo();
    // run_delay_demo();
    // run_reverb_demo();
    run_sequencer_demo();
    return 0;
}
