#include <vector>
#include "audio-station-c.h"
#include "audio-station.hpp"
#include "audio-signal.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();

    station->init();
    
    // TODO Move behind some instrument or something
    std::vector<double> frequencies {
        65.40639, // C2
        73.41619, // D2
        82.40689, // E2
        87.30706, // F2
        97.99886, // G2
        110.0000, // A2
        123.4708, // B2
        130.8128, // C3
        146.8324, // D3
        164.8138, // E3
        174.6141, // F3
        195.9977, // G3
        220.0000, // A3
        246.9417, // B3
    };
    
    std::vector<AudioSignal> signals;
    for (int i = 0; i < frequencies.size(); i++) {
        signals.push_back({
            .waveform = Waveform::Sine,
            .frequency = frequencies[i],
            .amplitude = 0.5,
            .live = false
        });
    }
    
    station->add_signals(signals);
    
    return reinterpret_cast<AudioStationHandle>(station);
}

void audio_station_play(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    station->play();
}

void audio_station_stop(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    station->stop();
}

void audio_station_set_signal_live(AudioStationHandle handle, int signal_id) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    station->set_signal_live(signal_id, true);
}

void audio_station_set_signal_silent(AudioStationHandle handle, int signal_id) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    station->set_signal_live(signal_id, false);
}

void audio_station_dispose(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    delete station;
}
