#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "note.hpp"
#include "oscillator.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

void test_oscillator_quiet_by_default() {
    Oscillator oscillator;
    assert_equal(0, oscillator.render());
}

void test_oscillator_play_and_stop() {
    Oscillator oscillator;
    oscillator.play();
    assert_equal(0, oscillator.render());
    oscillator.stop();
    assert_equal(0, oscillator.render());
}

void audiostation::run_oscillator_tests() {
    test_oscillator_quiet_by_default();
    test_oscillator_play_and_stop();
}
