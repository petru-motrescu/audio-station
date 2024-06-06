# Audio Station

A toy digital audio station for Mac.

The project consists of two parts:
- a library for generating and playing sounds
- a DAW-like app that uses the library (coming soon)


### The audio library

Built on top of Core Audio, the audio library can generate audio signals and play them in real-time. The library is implemented in C++ and it features also a C api so that it can be easily used from any Swift of Objective-C app on Mac.

Here's an example that creates a few instruments and organizes them in a track (see the full version [here](audio-station-lib/test/main.cpp)):
```cpp
void run_track_demo() {
    AudioStation station;
    station.init();

    Drum kick({
        .attack = { .wave = Wave::Triangle, .frequency = 150, .amplitude = 0.3 },
        .release = { .wave = Wave::Sine, .frequency = 30, .amplitude = 1.0 },
        .duration = 150,
    });

    Drum click({
        .attack = { .wave = Wave::Triangle, .frequency = 2000, .amplitude = 0.2 },
        .release = { .wave = Wave::Sine, .frequency = 2000, .amplitude = 0.1 },
        .duration = 100,
    });

    Drum hihat({
        .attack = { .wave = Wave::Noise, .amplitude = 0.1 },
        .release = { .wave = Wave::Noise, .amplitude = 0.1 },
        .duration = 150,
    });

    Synth bass({
        .wave = Wave::Triangle,
        .amplitude = 0.6,
        .envelope = {
            .atack_duration = 5, 
            .decay_duration = 20, 
            .sustain_level = 0.9, 
            .release_duration = 400
        }
    });

    TrackLane kick_lane = build_kick_lane(kick);
    TrackLane click_lane = build_click_lane(click);
    TrackLane hihat_lane = build_hihat_lane(hihat);
    TrackLane bass_lane = build_bass_lane(bass);

    Track track { 
        .lanes = { 
            &kick_lane, &click_lane, &hihat_lane, &bass_lane
        }
    };

    station.play(&track);
    sleep(5000);

    station.stop();
}
```

To run the above example:
```bash
cd audio-station-lib
make build
make run
```


### The app

<img src="screenshot.png" width="800"/>

The app uses SceneKit for the graphics and the audio library to play some silly sounds. Very much a work in progress.


### References

Books:
- [Learning Core Audio, by Chris Adamson, Kevin Avila](https://www.oreilly.com/library/view/learning-core-audio/9780321636973/)
- [Physical audio signal processing, by Julius Orion Smith III](https://ccrma.stanford.edu/~jos/pasp/pasp.html)
- [Introduction to digital filters, by Julius Orion Smith III](https://ccrma.stanford.edu/~jos/filters/)

Articles:
- [A bit about reverb, by Nigel Redmon](https://www.earlevel.com/main/1997/01/19/a-bit-about-reverb/)
- [How To Get the Perfect Kick Drum Sound, by Output Mag](https://output.com/blog/get-perfect-kick-drum)

Wikipedia:
- [DAW](https://en.wikipedia.org/wiki/Digital_audio_workstation)
- [Wave](https://en.wikipedia.org/wiki/wave)
- [Envelope](https://en.wikipedia.org/wiki/Envelope_(music))
- [Drum kit](https://en.wikipedia.org/wiki/Drum_kit)
- [Delay effect](https://en.wikipedia.org/wiki/Delay_(audio_effect))
- [Reverb effect](https://en.wikipedia.org/wiki/Reverb_effect)
- [Impulse response](https://en.wikipedia.org/wiki/Impulse_response)
- [Piano key frequencies](https://en.wikipedia.org/wiki/Piano_key_frequencies)

Apple:
- [Apple Audio](https://developer.apple.com/audio/)
- [Apple Core Audio](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview)
- [Apple SceneKit](https://developer.apple.com/documentation/scenekit)


### Disclaimer

_Educational & fun purpose only, no guarantees, no promises. Not connected to my employer._
