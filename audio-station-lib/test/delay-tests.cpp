#include "delay.hpp"
#include "asserts.hpp"
#include "tests.hpp"
#include "test.hpp"
using namespace audiostation;

void audiostation::run_delay_tests() {

    test("Delay effect with full level", [] {
        Delay delay({.time = 3, .level = 1.0, .sample_rate = 1000});
        assert_equal_2(0, delay.render(0.1));
        assert_equal_2(0, delay.render(0.2));
        assert_equal_2(0, delay.render(0.3));
        assert_equal_2(0.1, delay.render(1.0));
        assert_equal_2(0.21, delay.render(1.0));
        assert_equal_2(0.3, delay.render(1.0));
        assert_equal_2(1.0, delay.render(1.0));
        assert_equal_2(1.0, delay.render(1.0));
        assert_equal_2(1.0, delay.render(1.0));
    });

    test("Delay effect with half level", [] {
        Delay delay({.time = 3, .level = 0.5, .sample_rate = 1000});
        assert_equal_2(0, delay.render(0.1));
        assert_equal_2(0, delay.render(0.2));
        assert_equal_2(0, delay.render(0.3));
        assert_equal_2(0.05, delay.render(1.0));
        assert_equal_2(0.10, delay.render(1.0));
        assert_equal_2(0.15, delay.render(1.0));
        assert_equal_2(0.50, delay.render(1.0));
        assert_equal_2(0.50, delay.render(1.0));
        assert_equal_2(0.50, delay.render(1.0));
    });
    
}