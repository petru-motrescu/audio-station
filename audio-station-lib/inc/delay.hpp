#ifndef AUDIO_STATION_DELAY_HPP
#define AUDIO_STATION_DELAY_HPP

#include <memory>
#include "audio-sample.hpp"
#include "config.hpp"
#include "effect.hpp"

namespace audiostation {

    struct DelayConfig {
        unsigned time = 250;
        double feedback = 0.0;
        double level = 0.25;
        bool debug = false;
        unsigned sample_rate = Config::SAMPLE_RATE;
    };

    struct DelayImpl;

    class Delay : public Effect {
    public:
        Delay();
        Delay(Delay&& other);
        Delay(DelayConfig config);
        virtual ~Delay();
    
        AudioSample render(AudioSample sample) override;
    
    private:
        std::unique_ptr<DelayImpl> impl;
    };
}

#endif // AUDIO_STATION_DELAY_HPP
