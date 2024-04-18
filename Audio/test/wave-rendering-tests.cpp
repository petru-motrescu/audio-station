#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include "wave-rendering.hpp"
#include "test-asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.00000000001;
constexpr double PI = M_PI;

void audiostation::test_sine_wave_rendering() {
    std::list<std::tuple<double, double, std::string>> triples {
        { 0.00000000000, PI/1, "pi/1" },
        { 1.00000000000, PI/2, "pi/2" },
        { 0.86602540378, PI/3, "pi/3" },
        { 0.70710678118, PI/4, "pi/4" },
        { 0.58778525229, PI/5, "pi/5" },
        { 0.50000000000, PI/6, "pi/6" },
        { 0.43388373911, PI/7, "pi/7" },
        { 0.38268343236, PI/8, "pi/8" },
    };

    for (auto [expected, phase, message] : triples) {
        auto actual = render_wave(Waveform::Sine, phase);
        assert_equal(expected, actual, EPSILON, message);
    }

    for (auto [expected, phase, message] : triples) {
        auto actual = render_wave(Waveform::Sine, -phase);
        assert_equal(-expected, actual, EPSILON, "-" + message);
    }
}

void audiostation::test_square_wave_rendering() {
    auto x = 0.00000001;
    std::list<std::tuple<double, double, std::string>> triples {
        { +1.0, 0  + x, "0  + x" },
        { +1.0, PI - x, "pi - x" },
        { +1.0, PI + 0, "pi + 0" },
        { -1.0, PI + x, "pi + x" },
        { -1.0, 2 * PI - x, "2 * pi - x" },
        { -1.0, 2 * PI + 0, "2 * pi + 0" },
        { +1.0, 2 * PI + x, "2 * pi + x" },
    };

    for (auto [expected, phase, message] : triples) {
        auto actual = render_wave(Waveform::Square, phase);
        assert_equal(expected, actual, EPSILON, message);
    }
}
