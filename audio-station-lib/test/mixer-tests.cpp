#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "asserts.hpp"
#include "mixer.hpp"
#include "oscillator.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_mixer_tests() {

    test("Mixer with 1 track", [] {
        Oscillator oscillator({ .wave = Wave::Square, .amplitude = 0.5 });
        oscillator.trigger();
        Track track({ .instrument = &oscillator });
        Mixer mixer({track});
        assert_equal(0.5, mixer.render());
    });

    test("Mixer with 2 tracks", [] {
        OscillatorConfig config({ .wave = Wave::Square, .amplitude = 0.5 });
        Oscillator oscillator_1(config);
        Oscillator oscillator_2(config);
        oscillator_1.trigger();
        oscillator_2.trigger();
        Track track_1({ .instrument = &oscillator_1 });
        Track track_2({ .instrument = &oscillator_2 });
        Mixer mixer({track_1, track_2});
        assert_equal(1.0, mixer.render());
    });
}
