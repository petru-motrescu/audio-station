#include "delay.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_delay_tests() {

    test("Delay effect with full level", [] {
        Delay delay({.time = 3, .level = 1.0, .sample_rate = 1000});
        assert_equal(0, delay.render(0.1));
        assert_equal(0, delay.render(0.2));
        assert_equal(0, delay.render(0.3));
        assert_equal(0.1, delay.render(1.0));
        assert_equal(0.2, delay.render(1.0));
        assert_equal(0.3, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
        assert_equal(1.0, delay.render(1.0));
    });

    test("Delay effect with half level", [] {
        Delay delay({.time = 3, .level = 0.5, .sample_rate = 1000});
        assert_equal(0, delay.render(0.1));
        assert_equal(0, delay.render(0.2));
        assert_equal(0, delay.render(0.3));
        assert_equal(0.05, delay.render(1.0));
        assert_equal(0.10, delay.render(1.0));
        assert_equal(0.15, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
        assert_equal(0.50, delay.render(1.0));
    });
    
}