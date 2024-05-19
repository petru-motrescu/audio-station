#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "track.hpp"
#include "wave-renderer.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.000000000000001;

void test_empty_track() {
    Track track;
    for (int i = 0; i < 100; i++) {
        assert_equal(0, track.render(), EPSILON, "");
    }
}

void audiostation::run_track_tests() {
    test_empty_track();
}