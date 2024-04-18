#ifndef AUDIO_STATION_AUDIO_RENDERER_HPP
#define AUDIO_STATION_AUDIO_RENDERER_HPP

#include <memory>
#include <vector>
#include <list>

namespace audiostation {

    struct AudioRendererImpl;

    struct AudioRenderer {
        AudioRenderer();
        ~AudioRenderer();

        void init();
        void play();
        void stop();

    private:
        std::unique_ptr<AudioRendererImpl> impl;
    };
}

#endif // AUDIO_STATION_AUDIO_RENDERER_HPP
