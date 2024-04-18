#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <vector>
#include "audio-renderer.hpp"
#include "wave-rendering.hpp"
#include "audio-renderer-tests.hpp"
#include "asserts.hpp"
using namespace audiostation;

constexpr double EPSILON = 0.000000000000001;

void audiostation::test_audio_renderer() {
    AudioRenderer renderer(44100);
    assert_equal(0.1, renderer.render(), EPSILON, "");
}
