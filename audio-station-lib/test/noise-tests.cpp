#include "noise.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_noise_tests() {

    test("Noise is quiet by default", [] {
        Noise noise({ .amplitude = 1.0 });
        assert_equal(0, noise.render());
    });

    test("Noise can play and stop", [] {
        Noise noise({ .amplitude = 1.0 });
        noise.play();

        double sum = 0.0;
        for (int i = 0; i < 100; i++) {
            sum += noise.render();
        }
        assert_true(sum != 0.0);
        
        noise.stop();
        assert_equal(0, noise.render());
    });

}
