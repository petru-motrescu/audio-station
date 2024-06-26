#ifndef AUDIO_STATION_DELAY_HPP
#define AUDIO_STATION_DELAY_HPP

#include <memory>
#include "config.hpp"
#include "effect.hpp"

namespace audiostation {

    struct DelayConfig {
        unsigned time = 250;
        double feedback = 0.0;
        double level = 0.25;
    // internal:
        bool debug = false;
        unsigned sample_rate = Config::SAMPLE_RATE;
    };

    struct DelayImpl;

    struct Delay : public Effect {
        Delay();
        Delay(Delay&& other);
        Delay(DelayConfig config);
        virtual ~Delay();
    
    // internal:
        double render(double sample) override;
    
    private:
        std::unique_ptr<DelayImpl> impl;
    };
}

#endif // AUDIO_STATION_DELAY_HPP
