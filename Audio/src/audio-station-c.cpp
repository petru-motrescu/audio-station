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
        32.70320, // C1
        34.64783, // CD1
        36.70810, // D1
        38.89087, // DE1
        41.20344, // E1
        43.65353, // F1
        46.24930, // FG1
        48.99943, // G1
        51.91309, // GA1
        55.00000, // A1
        58.27047, // AB1
        61.73541, // B1
        // -----
        65.40639, // C2
        69.29566, // CD2
        73.41619, // D2
        77.78175, // DE2
        82.40689, // E2
        87.30706, // F2
        92.49861, // FG2
        97.99886, // G2
        103.8262, // GA2
        110.0000, // A2
        116.5409, // AB2
        123.4708, // B2
        // -----
        130.8128, // C3
        138.5913, // CD3
        146.8324, // D3
        155.5635, // DE3
        164.8138, // E3
        174.6141, // F3
        184.9972, // FG3
        195.9977, // G3
        207.6523, // GA3
        220.0000, // A3
        233.0819, // AB3
        246.9417, // B3
    };
    
    std::vector<AudioSignal> signals;
    for (int i = 0; i < frequencies.size(); i++) {
        signals.push_back({
            .waveform = Waveform::Square,
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
