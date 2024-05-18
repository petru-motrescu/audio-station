#ifndef AUDIO_STATION_H
#define AUDIO_STATION_H

#ifdef __cplusplus
extern "C" {
#endif

typedef long AudioStationHandle;
typedef long SynthHandle;

AudioStationHandle audio_station_init();
void audio_station_dispose(AudioStationHandle handle);

SynthHandle synth_init(AudioStationHandle handle);
void synth_play_note(SynthHandle handle, int note);
void synth_stop_note(SynthHandle handle, int note);
void synth_dispose(SynthHandle handle);

#ifdef __cplusplus
}
#endif

#endif // AUDIO_STATION_H
