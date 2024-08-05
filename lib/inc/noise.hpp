#ifndef AUDIO_STATION_NOISE_HPP
#define AUDIO_STATION_NOISE_HPP

#include <memory>
#include "audio-sample.hpp"
#include "instrument.hpp"

namespace audiostation {

    struct NoiseConfig {
        double amplitude = 0.05;
        bool is_live = false;
    };

    struct NoiseImpl;

    class Noise : public Instrument {
    public:
        Noise();
        Noise(NoiseConfig config);
        ~Noise();

        void trigger(Note note = Note::C4) override;
        void release(Note note = Note::C4) override;
        AudioSample render() override;

    private:
        std::unique_ptr<NoiseImpl> impl;
    };
}

#endif // AUDIO_STATION_NOISE_HPP
