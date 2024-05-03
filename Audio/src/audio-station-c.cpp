#include "audio-station-c.h"
#include "audio-station.hpp"
#include "audio-signal.hpp"
using namespace audiostation;

AudioStationHandle audio_station_init() {
    auto station = new AudioStation();
    
    // TODO Let caller provide the signals
    station->init();
    station->add({ .waveform = Waveform::Sine, .frequency = 100, .amplitude = 0.2 });
    
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

void audio_station_dispose(AudioStationHandle handle) {
    auto station = reinterpret_cast<AudioStation*>(handle);
    delete station;
}
