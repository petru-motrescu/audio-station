#ifndef AUDIO_STATION_H
#define AUDIO_STATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long AudioStationHandle;

AudioStationHandle audio_station_init();
void audio_station_play(AudioStationHandle handle);
void audio_station_stop(AudioStationHandle handle);
void audio_station_dispose(AudioStationHandle handle);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_STATION_H
