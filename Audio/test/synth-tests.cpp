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
    }
}

void test_synth_play_note() {
    Synth synth;
    for (auto& note : Notes::piano_notes) {
        auto note_str = Notes::to_string(note);
        synth.play_note(note);
        assert_true(synth.is_note_live(note), note_str);
        synth.stop_note(note);
        assert_false(synth.is_note_live(note), note_str);
    }
}

void audiostation::run_synth_tests() {
    test_synth_quiet_by_default();
    test_synth_play_note();
}