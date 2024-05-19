#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include "renderer.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.00000000001;
constexpr double PI = M_PI;

void test_sine_wave_rendering() {
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
        auto actual = Renderer::render_wave(Waveform::Sine, phase);
        assert_equal(expected, actual, EPSILON, message);
    }

    for (auto [expected, phase, message] : triples) {
        auto actual = Renderer::render_wave(Waveform::Sine, -phase);
        assert_equal(-expected, actual, EPSILON, "-" + message);
    }
}

void test_square_wave_rendering() {
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
        auto actual = Renderer::render_wave(Waveform::Square, phase);
        assert_equal(expected, actual, EPSILON, message);
    }
}

void test_next_phase() {
    constexpr unsigned int frequency = 100;
    constexpr unsigned int sample_rate = 800;

    // next_phase = current_phase + 2 * pi * 100 / 800
    // next_phase = current_phase + pi / 4
    constexpr double x = PI / 4;

    std::list<std::tuple<double, double, std::string>> triples {
        { -8 * x, 1 * x, "-8x" },
        { -7 * x, 2 * x, "-7x" },
        { -6 * x, 3 * x, "-6x" },
        { -5 * x, 4 * x, "-5x" },
        { -4 * x, 5 * x, "-4x" },
        { -3 * x, 6 * x, "-3x" },
        { -2 * x, 7 * x, "-2x" },
        { -1 * x, 0 * x, "-1x" }, // <-- wrap around
        { 0  * x, 1 * x, "+0x" },
        { +1 * x, 2 * x, "+1x" },
        { +2 * x, 3 * x, "+2x" },
        { +3 * x, 4 * x, "+3x" },
        { +4 * x, 5 * x, "+4x" },
        { +5 * x, 6 * x, "+5x" },
        { +6 * x, 7 * x, "+6x" },
        { +7 * x, 0 * x, "+7x" }, // <-- wrap around
        { +8 * x, 1 * x, "+8x" },
    };

    for (auto [current_phase, expected, message] : triples) {
        auto actual = Renderer::next_phase(current_phase, frequency, sample_rate);
        assert_equal(expected, actual, EPSILON, message);
    }
}

void audiostation::run_renderer_tests() {
    test_sine_wave_rendering();
    test_square_wave_rendering();
    test_next_phase();
}