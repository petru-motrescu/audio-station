#ifndef AUDIO_STATION_DELAY_HPP
#define AUDIO_STATION_DELAY_HPP

#include <memory>
#include "effect.hpp"

namespace audiostation {

    struct DelayConfig {
        unsigned time = 250;
        double level = 0.25;
    };

    struct DelayImpl;

    struct Delay : public Effect {
        Delay();
        Delay(DelayConfig config);
        ~Delay();
    
    // internal:
        double render(double sample) override;
    
    private:
        std::unique_ptr<DelayImpl> impl;
    };
}

#endif // AUDIO_STATION_DELAY_HPP
