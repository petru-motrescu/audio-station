#include "audio-station-c.h"
#include "audio-station.hpp"
#include "audio-signal.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();
    
    // TODO Let caller provide the signals
    station->init();
    station->add_signal({
        .waveform = Waveform::Sine,
        .frequency = 220.0000,
        .amplitude = 0.5,
        .live = false
    });
    
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
