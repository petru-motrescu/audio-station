#ifndef AUDIO_STATION_AUDIO_RENDERER_HPP
#define AUDIO_STATION_AUDIO_RENDERER_HPP

#include <memory>
#include "audio-signal.hpp"

namespace audiostation {

    struct AudioRendererImpl;

    struct AudioRenderer {
        AudioRenderer(unsigned sample_rate);
        ~AudioRenderer();

        void add(audiostation::AudioSignal signal);
        double render();

    private:
        std::unique_ptr<AudioRendererImpl> impl;
    };
}

#endif // AUDIO_STATION_AUDIO_RENDERER_HPP
