#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include <tuple>
#include <thread>
#include <chrono>
#include "audio-signal.hpp"
#include "audio-station.hpp"
#include "frequency.hpp"
#include "synth.hpp"
#include "tests.hpp"
using namespace audiostation;

void run_tests() {
    std::cout << "🧪 Running tests" << std::endl;
    run_wave_rendering_tests();
    run_audio_rendering_tests();
    run_synth_tests();
    std::cout << "✅ All tests done" << std::endl;
}

void run_readme_demo() {
    std::vector<AudioSignal> signals {
        { .waveform = Waveform::Sine, .frequency = Frequency::C2, .amplitude = 0.4, .live = true },
        { .waveform = Waveform::Sine, .frequency = Frequency::C4, .amplitude = 0.3, .live = true },
        { .waveform = Waveform::Sine, .frequency = Frequency::F4, .amplitude = 0.2, .live = true },
        { .waveform = Waveform::Square, .frequency = Frequency::C5, .amplitude = 0.01, .live = true },
    };

    AudioStation station;
    station.init();
    station.add_signals(signals);
    station.play();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    station.stop();
}

void run_piano_demo() {
    std::vector<AudioSignal> signals;
    
    // Idealized standard piano keys
    for (int i = 1; i <= 89; i++) {
        auto frequency = pow(2, (i - 49) / 12.0) * 440;
        std::cout << i << " = " << frequency << std::endl;
        signals.push_back({ 
            .waveform = Waveform::Sine, 
            .frequency = frequency, 
            .amplitude = 0.5
        });
    }

    AudioStation station;
    station.init();
    station.add_signals(signals);
    station.play();
    for (int i = 0; i < signals.size(); i++) {
        station.set_signal_live(i, true);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        station.set_signal_live(i, false);
    }
    station.stop();
}

void run_synth_demo() {
    AudioStation station;
    station.init();
    station.play();
    
    Synth synth;
    station.add_synth(&synth);
    
    for (auto& note : Notes::piano_notes) {
        synth.play_note(note);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        synth.stop_note(note);
    }
    
    station.stop();
}

int main() {
    // run_tests();
    // run_readme_demo();
    // run_piano_demo();
    run_synth_demo();
    return 0;
}
