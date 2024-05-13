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
    for (int i = Notes::to_int(Synth::FIRST_NOTE); i <= Notes::to_int(Synth::LAST_NOTE); i++) {
        auto note = Notes::from_int(i);
        assert_false(synth.is_note_live(note), std::to_string(i));
    }
}

void test_synth_play_note() {
    Synth synth;
    for (int i = Notes::to_int(Synth::FIRST_NOTE); i <= Notes::to_int(Synth::LAST_NOTE); i++) {
        auto note = Notes::from_int(i);
        synth.play_note(note);
        assert_true(synth.is_note_live(note), std::to_string(i));
        synth.stop_note(note);
        assert_false(synth.is_note_live(note), std::to_string(i));
    }
}

void audiostation::run_synth_tests() {
    test_synth_quiet_by_default();
    test_synth_play_note();
}