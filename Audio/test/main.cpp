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

    std::vector<AudioSignal> signals;
    
    // Idealized standard piano keys
    for (int i = 1; i <= 89; i++) {
        auto frequency = pow(2, (i - 49) / 12.0) * 440;
        std::cout << i << " = " << frequency << std::endl;
        signals.push_back({ 
            .waveform = Waveform::Sine, 
            .frequency = frequency, 
            .amplitude = 0.01
        });
    }

    AudioStation station;
    station.init();
    station.add(signals);
    station.play();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    station.stop();

    return 0;
}
