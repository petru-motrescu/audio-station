# Audio Station

A toy digital audio station for Mac.

The project consists of two parts:
- a library for generating and playing sounds
- a DAW-like app that uses the library (coming soon)


### The library

The purpose of the library is to generate and play sounds from any C++ app on Mac.

A simple example:
```cpp
std::vector<AudioSignal> signals {
    { .waveform = Waveform::Sine, .frequency = 65.40639, .amplitude = 0.4, .live = true },
    { .waveform = Waveform::Sine, .frequency = 261.6256, .amplitude = 0.3, .live = true },
    { .waveform = Waveform::Sine, .frequency = 349.2282, .amplitude = 0.2, .live = true },
    { .waveform = Waveform::Square, .frequency = 523.2511, .amplitude = 0.01, .live = true },
};

AudioStation station;
station.init();
station.add_signals(signals);
station.play();
std::this_thread::sleep_for(std::chrono::seconds(3));
station.stop();
```

To run the above example:
```bash
cd Audio
make build
make run
```


### The app

_soon_


### Documentation

Audio:
- [Wiki > DAW](https://en.wikipedia.org/wiki/Digital_audio_workstation)
- [Wiki > Waveform](https://en.wikipedia.org/wiki/Waveform)
- [Apple > Audio](https://developer.apple.com/audio/)
- [Apple > Core Audio](https://developer.apple.com/library/archive/documentation/MusicAudio/Conceptual/CoreAudioOverview)
- [Wiki > Piano key frequencies](https://en.wikipedia.org/wiki/Piano_key_frequencies)

Graphics:
- [Apple > SceneKit](https://developer.apple.com/documentation/scenekit)
