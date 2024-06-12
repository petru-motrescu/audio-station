#include "delay.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_delay_tests() {

    test("Delay effect with full level", [] {
        Delay delay({.time = 3, .level = 1.0, .sample_rate = 1000});
        assert_equal(0.0, delay.render(0.1));
        assert_equal(0.0, delay.render(0.2));
        assert_equal(0.0, delay.render(0.3));
        assert_equal(0.1, delay.render(1.0));
        assert_equal(0.2, delay.render(1.0));
        assert_equal(0.3, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
    });

    test("Delay effect with half level", [] {
        Delay delay({.time = 3, .level = 0.5, .sample_rate = 1000});
        assert_equal(0.00, delay.render(0.1));
        assert_equal(0.00, delay.render(0.2));
        assert_equal(0.00, delay.render(0.3));
        assert_equal(0.05, delay.render(1.0));
        assert_equal(0.10, delay.render(1.0));
        assert_equal(0.15, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
    });
    
    test("Delay effect with full feedback", [] {
        Delay delay({.time = 3, .level = 1.0, .feedback = 1.0, .sample_rate = 1000});
        assert_equal(0.0, delay.render(0.1));
        assert_equal(0.0, delay.render(0.2));
        assert_equal(0.0, delay.render(0.3));
        assert_equal(0.1, delay.render(1.0));
        assert_equal(0.2, delay.render(1.0));
        assert_equal(0.3, delay.render(1.0));
        assert_equal(1.1, delay.render(1.0));
        assert_equal(1.2, delay.render(1.0));
        assert_equal(1.3, delay.render(1.0));
        assert_equal(2.1, delay.render(1.0));
        assert_equal(2.2, delay.render(1.0));
        assert_equal(2.3, delay.render(1.0));
    });

    test("Delay effect with half feedback", [] {
        Delay delay({.time = 3, .level = 1.0, .feedback = 0.5, .sample_rate = 1000});
        assert_equal(0.000, delay.render(0.1));
        assert_equal(0.000, delay.render(0.2));
        assert_equal(0.000, delay.render(0.3));
        assert_equal(0.100, delay.render(1.0));
        assert_equal(0.200, delay.render(1.0));
        assert_equal(0.300, delay.render(1.0));
        assert_equal(1.050, delay.render(1.0));
        assert_equal(1.100, delay.render(1.0));
        assert_equal(1.150, delay.render(1.0));
        assert_equal(1.525, delay.render(1.0));
        assert_equal(1.550, delay.render(1.0));
        assert_equal(1.575, delay.render(1.0));
    });

    test("Delay effect with half level and feedback", [] {
        Delay delay({.time = 3, .level = 0.5, .feedback = 0.5, .sample_rate = 1000});
        assert_equal(0.000000, delay.render(0.1));
        assert_equal(0.000000, delay.render(0.2));
        assert_equal(0.000000, delay.render(0.3));
        assert_equal(0.050000, delay.render(1.0));
        assert_equal(0.100000, delay.render(1.0));
        assert_equal(0.150000, delay.render(1.0));
        assert_equal(0.512500, delay.render(1.0));
        assert_equal(0.525000, delay.render(1.0));
        assert_equal(0.537500, delay.render(1.0));
        assert_equal(0.628125, delay.render(1.0));
        assert_equal(0.631250, delay.render(1.0));
        assert_equal(0.634375, delay.render(1.0));
    });
}