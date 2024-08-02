#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "synth.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_synth_tests() {

    test("Synth is quiet by default", [] {
        Synth synth;
        for (auto& note : Notes::piano_notes) {
            assert_false(synth.is_note_live(note), Notes::to_string(note));
            assert_equal(0, synth.render());
        }
    });

    test("Triangle synth with blank envelope", [] {
        auto note = Note::A3;
        Synth synth({ 
            .wave = Wave::Triangle, 
            .amplitude = 1.0,
            .envelope = EnvelopeConfig(),
            .sample_rate = (unsigned) Notes::get_frequency(note) * 8,
        });

        synth.trigger(note);
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
    });

    test("Triangle synth with proper envelope", [] {
        Note note = Note::A3;
        unsigned sample_rate = Notes::get_frequency(note) * 8;
        unsigned duration_of_8_ticks = 8 * 1000 / sample_rate;
        Synth synth({
            .wave = Wave::Triangle,
            .amplitude = 1.0,
            .envelope = {
                .attack_duration = duration_of_8_ticks,
                .decay_duration = duration_of_8_ticks,
                .sustain_level = 0.5,
                .release_duration = duration_of_8_ticks,
            },
            .sample_rate = sample_rate,
        });
        
        std::vector<double> actual_samples;

        synth.trigger(note);
        for (int i = 0; i < 8 * 3; i++) { 
            actual_samples.push_back(synth.render());
        }

        synth.release(note);
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
    });

}