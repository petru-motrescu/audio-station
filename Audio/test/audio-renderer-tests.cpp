#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "audio-renderer.hpp"
#include "wave-renderer.hpp"
#include "asserts.hpp"
#include "tests.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.000000000000001;

void test_audio_renderer_with_no_signals() {
    AudioRenderer renderer(44100);
    for (int i = 0; i < 100; i++) {
        assert_equal(0, renderer.render(), EPSILON, "");
    }
}

void audiostation::run_audio_rendering_tests() {
    test_audio_renderer_with_no_signals();
}