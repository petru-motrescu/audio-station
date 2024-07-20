#include "oscillator.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_oscillator_tests() {

    test("Oscillator is quiet by default", [] {
        Oscillator oscillator({});
        assert_equal(0, oscillator.render());
    });

    test("Oscillator can play and stop", [] {
        Oscillator oscillator({});
        oscillator.play();
        assert_equal(0, oscillator.render());
        oscillator.stop();
        assert_equal(0, oscillator.render());
    });

}
