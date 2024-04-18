#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include "tests.hpp"
#include "audio-renderer.hpp"
using namespace audiostation;

void run_tests() {
    std::cout << "🧪 Running tests" << std::endl;
    test_sine_wave_rendering();
    test_square_wave_rendering();
    std::cout << "✅ All tests done" << std::endl;
}

int main() {
    run_tests();

    AudioRenderer renderer;
    renderer.init();
    renderer.play();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    renderer.stop();

    return 0;
}
