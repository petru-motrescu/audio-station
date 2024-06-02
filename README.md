# Audio Station

A toy digital audio station for Mac.

The project consists of two parts:
- a library for generating and playing sounds
- a DAW-like app that uses the library (coming soon)


### The audio library

Built on top of Core Audio, the audio library can generate audio signals and play them in real-time. For better or for worse the library has been implemented in C++. There is a C api available as well so that it can be easily used from any Swift of Objective-C app on Mac.

Example (see the full version [here](Audio/test/main.cpp)):
```cpp
void run_track_demo() {
    AudioStation station;
    station.init();

    Drum kick({
        .wave = Wave::Sine,
        .atack_frequency = 120,
        .decay_frequency = 30,
        .decay_millis = 150,
        .amplitude = 0.5,
    });

    Drum click({
        .wave = Wave::Sine,
        .atack_frequency = 2000,
        .decay_frequency = 2000,
        .decay_millis = 100,
        .amplitude = 0.2,
    });

    Drum hihat({
        .wave = Wave::Noise,
        .decay_millis = 150,
        .amplitude = 0.1,
    });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.6,
        .envelope = {
            .atack_millis = 5, 
            .decay_millis = 20, 
            .sustain_level = 0.9, 
            .release_millis = 400
        }
    });

    TrackLane kick_lane = build_kick_lane(kick);
    TrackLane click_lane = build_click_lane(click);
    TrackLane hihat_lane = build_hihat_lane(hihat);
    TrackLane bass_lane = build_bass_lane(bass);

    Track track { 
        .lanes = { &kick_lane, &click_lane, &hihat_lane, &bass_lane },
        .debug = true,
    };

    station.play(&track);
    sleep(5000);

    station.stop();
}
```

To run the above example:
```bash
cd Audio
make build
make run
```


### The app

<img src="screenshot.png" width="800"/>

The app uses SceneKit for the graphics and the audio library to play some silly sounds. Very much a work in progress.


### Documentation

- [DAW, by Wikipedia](https://en.wikipedia.org/wiki/Digital_audio_workstation)
- [wave, by Wikipedia](https://en.wikipedia.org/wiki/wave)
- [waves, by Josh Comeau](https://pudding.cool/2018/02/waves/)
- [Envelope, by Wikipedia](https://en.wikipedia.org/wiki/Envelope_(music))
- [Piano key frequencies, by Wikipedia](https://en.wikipedia.org/wiki/Piano_key_frequencies)
- [Drum kit, by Wikipedia](https://en.wikipedia.org/wiki/Drum_kit)
- [How To Get the Perfect Kick Drum Sound, by Output Mag](https://output.com/blog/get-perfect-kick-drum)
- [Apple Audio](https://developer.apple.com/audio/)
- [Apple Core Audio](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview)
- [Apple SceneKit](https://developer.apple.com/documentation/scenekit)


### Footnote

_Educational purpose only, no guarantees, no promises. Not connected to my employer._
