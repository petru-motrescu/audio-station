#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include "audio-signal.hpp"
#include "audio-station.hpp"
#include "tests.hpp"
using namespace audiostation;

void run_tests() {
    std::cout << "🧪 Running tests" << std::endl;
    run_wave_rendering_tests();
    run_audio_rendering_tests();
    std::cout << "✅ All tests done" << std::endl;
}

int main() {
    run_tests();

    AudioStation station;
    station.init();
    station.add({ .waveform = Waveform::Sine, .frequency = 27.50000, .amplitude = 0.5 });
    station.play();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    station.stop();

    return 0;
}
