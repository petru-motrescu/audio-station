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
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
    });

    test("Delay effect with half feedback", [] {
        Delay delay({.time = 3, .level = 1.0, .feedback = 0.5, .sample_rate = 1000});
        assert_equal(0.000, delay.render(0.1));
        assert_equal(0.000, delay.render(0.2));
        assert_equal(0.000, delay.render(0.3));
        assert_equal(0.100, delay.render(1.0));
        assert_equal(0.200, delay.render(1.0));
        assert_equal(0.300, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
    });

    test("Delay effect with half level and feedback", [] {
        Delay delay({.time = 3, .level = 0.5, .feedback = 0.5, .sample_rate = 1000});
        assert_equal(0.00000000, delay.render(0.1));
        assert_equal(0.00000000, delay.render(0.2));
        assert_equal(0.00000000, delay.render(0.3));
        assert_equal(0.05000000, delay.render(1.0));
        assert_equal(0.10000000, delay.render(1.0));
        assert_equal(0.15000000, delay.render(1.0));
        assert_equal(0.51250000, delay.render(1.0));
        assert_equal(0.52500000, delay.render(1.0));
        assert_equal(0.53750000, delay.render(1.0));
        assert_equal(0.62812500, delay.render(1.0));
        assert_equal(0.63125000, delay.render(1.0));
        assert_equal(0.63437500, delay.render(1.0));
        assert_equal(0.65703125, delay.render(1.0));
        assert_equal(0.65781250, delay.render(1.0));
        assert_equal(0.65859375, delay.render(1.0));
    });

    test("Delay feedback should fade off", [] {
        Delay delay({.time = 2, .level = 1.0, .feedback = 0.5, .sample_rate = 1000});
        assert_equal(0.0000, delay.render(1.0));
        assert_equal(0.0000, delay.render(0.0));
        assert_equal(1.0000, delay.render(0.0));
        assert_equal(0.0000, delay.render(0.0));
        assert_equal(0.5000, delay.render(0.0));
        assert_equal(0.0000, delay.render(0.0));
        assert_equal(0.2500, delay.render(0.0));
        assert_equal(0.0000, delay.render(0.0));
        assert_equal(0.1250, delay.render(0.0));
        assert_equal(0.0000, delay.render(0.0));
        assert_equal(0.0625, delay.render(0.0));
    });
}