#include "noise.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
#include "test.hpp"
using namespace audiostation;

void audiostation::noise_tests() {

    test("Noise is quiet by default", [] {
        Noise noise({ .amplitude = 1.0 });
        assert_equal(0, noise.render());
    });

    test("Noise can play and stop", [] {
        Noise noise({ .amplitude = 1.0 });
        noise.trigger();

        double sum = 0.0;
        for (int i = 0; i < 100; i++) {
            sum += noise.render();
        }
        assert_true(sum != 0.0);
        
        noise.release();
        assert_equal(0, noise.render());
    });

}
