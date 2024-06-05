#include "delay.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

void test_delay_with_full_level() {
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
}

void test_delay_with_half_level() {
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
}

void audiostation::run_delay_tests() {
    test_delay_with_full_level();
    test_delay_with_half_level();
}