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
#include "mixer.hpp"
#include "noise.hpp"
#include "oscillator.hpp"
#include "reverb.hpp"
#include "sequencer.hpp"
#include "synth.hpp"
using namespace audiostation;

constexpr unsigned bar = Config::SAMPLE_RATE / 2;
constexpr unsigned half = bar / 2;
constexpr unsigned quart = bar / 4;
constexpr unsigned eighth = bar / 8;

void sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

Sequencer build_kick_sequencer() {
    std::vector<SequenceNote> notes = { 
        { .offset = 0 * bar }, 
        { .offset = 2 * bar + half },
    };

    return Sequencer({
        .loop_enabled = false,
        .blocks = {
            { .offset = 4 * bar * 0, .notes = notes },
            { .offset = 4 * bar * 1, .notes = notes },
            { .offset = 4 * bar * 2, .notes = notes },
            { .offset = 4 * bar * 3, .notes = notes },
        }
    });
}

Sequencer build_click_sequencer() {
    std::vector<SequenceNote> notes = { 
        { .offset = 2 * bar }
    };
    
    return Sequencer({
        .loop_enabled = false,
        .blocks = {
            { .offset = 4 * bar * 2, .notes = notes },
            { .offset = 4 * bar * 3, .notes = notes },
        }
    });
}

Sequencer build_hihat_sequencer() {
    std::vector<SequenceNote> notes = { 
        { .offset = 1 * bar + half, .length = 1 * eighth },
        { .offset = 3 * bar + half, .length = 1 * eighth },
    };

    return Sequencer({
        .loop_enabled = false,
        .blocks = {
            { .offset = 4 * bar * 2, .notes = notes },
            { .offset = 4 * bar * 3, .notes = notes },
        }
    });
}

Sequencer build_bass_sequencer() {
    std::vector<SequenceNote> notes = {
        { .offset = 2 * bar + half,      .length = 3 * quart,  .note = Note::C2 },
        { .offset = 3 * bar + 1 * quart, .length = 1 * quart,  .note = Note::A1 },
        { .offset = 3 * bar + 2 * quart, .length = 1 * eighth, .note = Note::A1 },
        { .offset = 3 * bar + 3 * quart, .length = 1 * eighth, .note = Note::A1 },
    };

    return Sequencer({
        .loop_enabled = false,
        .blocks = {
            { .offset = 4 * bar * 0, .notes = notes },
            { .offset = 4 * bar * 1, .notes = notes },
            { .offset = 4 * bar * 2, .notes = notes },
            { .offset = 4 * bar * 3, .notes = notes },
        }
    });
}

Sequencer build_lead_sequencer() {
    std::vector<SequenceNote> notes = {
        { .offset = 0 * bar, .length = 1 * eighth, .note = Note::B3 },
    };

    return Sequencer({
        .loop_enabled = false,
        .blocks = {
            { .offset = 4 * bar * 0, .notes = notes }
        }
    });
}

void run_song_demo() {
    AudioStation station;
    station.init();

    Drum kick;

    Drum click({
        .attack = { .wave = Wave::Triangle, .frequency = 2000, .amplitude = 0.2 },
        .release = { .wave = Wave::Sine, .frequency = 2000, .amplitude = 0.1 },
        .duration = 100,
    });

    Noise hihat({ .amplitude = 0.1 });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.4,
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
        .envelope = {
            .attack_duration = 5, 
            .decay_duration = 5, 
            .sustain_level = 1.0, 
            .release_duration = 40
        }
    });

    Delay delay({ .time = 80, .level = 0.6, .feedback = 0.75 });
    Reverb reverb;

    Sequencer kick_sequencer = build_kick_sequencer();
    Sequencer click_sequencer = build_click_sequencer();
    Sequencer hihat_sequencer = build_hihat_sequencer();
    Sequencer bass_sequencer = build_bass_sequencer();
    Sequencer lead_sequencer = build_lead_sequencer();

    Mixer mixer({ 
        Track({ .sequencer = &kick_sequencer, .instrument = &kick }),
        Track({ .sequencer = &click_sequencer, .instrument = &click, .effects = { &delay } }),
        Track({ .sequencer = &hihat_sequencer, .instrument = &hihat }),
        Track({ .sequencer = &bass_sequencer, .instrument = &bass }),
        Track({ .sequencer = &lead_sequencer, .instrument = &lead, .effects = { &reverb } }),
    });

    station.play(&mixer);
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
    Oscillator oscillator({
        .wave = Wave::Sine,
        .frequency = Frequency::C4,
        .amplitude = 0.25,
        .is_live = true,
    });

    AudioStation station;
    station.init();
    station.play(&oscillator);
    sleep(2000);
    station.stop();
}

void run_delay_demo() {
    Drum drum;
    Delay delay({ 
        .time = 250,
        .feedback = 0.99,
        .level = 0.75
    });

    Mixer mixer({ { .instrument = &drum, .effects = { &delay } } });

    AudioStation station;
    station.init();
    station.play(&mixer);

    for (int i = 0; i < 5; i++) {
        drum.trigger();
        sleep(5000);
    }
    
    station.stop();
}

void run_reverb_demo() {
    unsigned note_duration = (unsigned) 16 * M_PI;

    SynthConfig config({
        .wave = Wave::Triangle,
        .amplitude = 0.4,
        .envelope = {
            .attack_duration = 0, 
            .decay_duration = 0, 
            .sustain_level = 1.0,
            .release_duration = note_duration
        }
    });

    Synth synth_1(config);
    Synth synth_2(config);
    Reverb reverb;

    Mixer mixer({ 
        Track({ .instrument = &synth_1 }), 
        Track({ .instrument = &synth_2, .effects = { &reverb } })
    });

    AudioStation station;
    station.init();
    station.play(&mixer);
    
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
    Mixer mixer({ Track { .sequencer = &sequencer, .instrument = &drum } });

    AudioStation station;
    station.init();
    station.play(&mixer);
    sleep(5000);
    station.stop();
}

int main() {
    run_song_demo();
    // run_noise_demo();
    // run_oscillator_demo();
    // run_delay_demo();
    // run_reverb_demo();
    // run_sequencer_demo();
    return 0;
}
