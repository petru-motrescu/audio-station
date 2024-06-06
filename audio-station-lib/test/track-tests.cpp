#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "track.hpp"
#include "asserts.hpp"
#include "test-suite.hpp"
using namespace audiostation;

void audiostation::TestSuite::run_track_tests() {

    test("Empty track", [] {
        Track track;
        for (int i = 0; i < 100; i++) {
            assert_equal(0, track.render());
        }
    });
    
}
