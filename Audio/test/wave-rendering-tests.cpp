#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include "wave-rendering.hpp"
#include "test-asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

void audiostation::test_sine_wave_rendering() {
    std::list<std::tuple<double, double, std::string>> triples {
        { 0.00000000000, M_PI/1, "pi/1" },
        { 1.00000000000, M_PI/2, "pi/2" },
        { 0.86602540378, M_PI/3, "pi/3" },
        { 0.70710678118, M_PI/4, "pi/4" },
        { 0.58778525229, M_PI/5, "pi/5" },
        { 0.50000000000, M_PI/6, "pi/6" },
        { 0.43388373911, M_PI/7, "pi/7" },
        { 0.38268343236, M_PI/8, "pi/8" },
    };

    constexpr double epsilon = 0.00000000001;

    for (auto [expected, phase, message] : triples) {
        auto actual = render_wave(Waveform::Sine, phase);
        assert_equal(expected, actual, epsilon, message);
    }

    for (auto [expected, phase, message] : triples) {
        auto actual = render_wave(Waveform::Sine, -phase);
        assert_equal(-expected, actual, epsilon, "-" + message);
    }
}
