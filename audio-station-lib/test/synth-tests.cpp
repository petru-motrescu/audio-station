#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "synth.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

void test_synth_quiet_by_default() {
    Synth synth;
    for (auto& note : Notes::piano_notes) {
        assert_false(synth.is_note_live(note), Notes::to_string(note));
        assert_equal(0, synth.render());
    }
}

void test_triangle_synth_with_blank_envelope() {
    Synth synth({ .wave = Wave::Triangle, .amplitude = 1.0 });

    auto note = Note::A3;
    synth.set_sample_rate(Notes::get_frequency(note) * 8);
    synth.set_renderable_envelope({
        .atack_ticks = 0,
        .decay_ticks = 0,
        .sustain_level = 1,
        .release_ticks = 0
    });

    synth.play_note(note);
    std::vector<double> actual_samples;
    for (int i = 0; i < 8 * 4; i++) {
        actual_samples.push_back(synth.render());
    }

    std::vector<double> expected_samples {
        0, 0.5, 1, 0.5, 0, -0.5, -1, -0.5, 
        0, 0.5, 1, 0.5, 0, -0.5, -1, -0.5, 
        0, 0.5, 1, 0.5, 0, -0.5, -1, -0.5, 
        0, 0.5, 1, 0.5, 0, -0.5, -1, -0.5,
    };

    assert_equal(expected_samples, actual_samples);
}

void test_triangle_synth_with_proper_envelope() {
    Synth synth({ .wave = Wave::Triangle, .amplitude = 1.0 });

    auto note = Note::A3;
    synth.set_sample_rate(Notes::get_frequency(note) * 8);
    synth.set_renderable_envelope({
        .atack_ticks = 8,
        .decay_ticks = 8,
        .sustain_level = 0.5,
        .release_ticks = 8
    });

    std::vector<double> actual_samples;

    synth.play_note(note);
    for (int i = 0; i < 8 * 3; i++) { 
        actual_samples.push_back(synth.render());
    }

    synth.stop_note(note);
    for (int i = 0; i < 8 * 1; i++) { 
        actual_samples.push_back(synth.render());
    }

    std::vector<double> expected_samples { 
        0, 0.06250, 0.250, 0.18750, 0, -0.31250, -0.750, -0.43750,  // attack
        0, 0.46875, 0.875, 0.40625, 0, -0.34375, -0.625, -0.28125,  // decay
        0, 0.25000, 0.500, 0.25000, 0, -0.25000, -0.500, -0.25000,  // sustain
        0, 0.21875, 0.375, 0.15625, 0, -0.09375, -0.125, -0.03125,  // release
    };

    assert_equal(expected_samples, actual_samples);
}

void audiostation::run_synth_tests() {
    test_synth_quiet_by_default();
    test_triangle_synth_with_blank_envelope();
    test_triangle_synth_with_proper_envelope();
}