#include <list>
#include <tuple>
#include <iomanip>
#include "oscillator.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
#include "test.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.00000000001;
constexpr double PI = M_PI;

void audiostation::oscillator_tests() {

    test("Sine wave rendering", [] {
        Oscillator oscillator({ .wave = Wave::Sine, .amplitude = 1.0 });
        oscillator.trigger();

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
            oscillator.set_phase(phase);
            auto actual = oscillator.render();
            assert_equal(expected, actual, EPSILON, message.c_str());
        }

        for (auto [expected, phase, message] : triples) {
            oscillator.set_phase(-phase);
            auto actual = oscillator.render();
            assert_equal(-expected, actual, EPSILON, "-" + message);
        }
    });

    test("Square wave rendering", [] {
        Oscillator oscillator({ .wave = Wave::Square, .amplitude = 1.0 });
        oscillator.trigger();

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
            oscillator.set_phase(phase);
            auto actual = oscillator.render();
            assert_equal(expected, actual, EPSILON, message);
        }
    });

    test("Triangle wave rendering", [] {
        Oscillator oscillator({ .wave = Wave::Triangle, .amplitude = 1.0 });
        oscillator.trigger();

        std::list<std::tuple<double, double, std::string>> triples {
            {  0.00000000000, 0.00 * PI, "0.00 * PI" },
            {  0.50000000000, 0.25 * PI, "0.25 * PI" },
            {  1.00000000000, 0.50 * PI, "0.50 * PI" },
            {  0.50000000000, 0.75 * PI, "0.75 * PI" },
            {  0.00000000000, 1.00 * PI, "1.00 * PI" },
            { -0.50000000000, 1.25 * PI, "1.25 * PI" },
            { -1.00000000000, 1.50 * PI, "1.50 * PI" },
            { -0.50000000000, 1.75 * PI, "1.75 * PI" },
            {  0.00000000000, 2.00 * PI - EPSILON, "2.00 * PI - epsilon" }, // if phase == 2PI it wraps back to 0
        };

        for (auto [expected, phase, message] : triples) {
            oscillator.set_phase(phase);
            auto actual = oscillator.render();
            assert_equal(expected, actual, EPSILON, message);
        }
    });

    test("Next rendering phase", [] {
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

        Oscillator oscillator({ .frequency = 100, .amplitude = 1.0, .sample_rate = 800 });
        oscillator.trigger();

        for (auto [current_phase, expected, message] : triples) {
            oscillator.set_phase(current_phase);
            oscillator.render();
            auto actual = oscillator.get_phase();
            assert_equal(expected, actual, EPSILON, message);
        }
    });

    test("Oscillator is quiet by default", [] {
        Oscillator oscillator({});
        assert_equal(0, oscillator.render());
    });

    test("Oscillator can play and stop", [] {
        Oscillator oscillator({});
        oscillator.trigger();
        assert_equal(0, oscillator.render());
        oscillator.release();
        assert_equal(0, oscillator.render());
    });

}
