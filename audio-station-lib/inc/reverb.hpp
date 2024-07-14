#ifndef AUDIO_STATION_REVERB_HPP
#define AUDIO_STATION_REVERB_HPP

#include <memory>
#include "effect.hpp"

namespace audiostation {

    struct ReverbConfig {
        double size = 0.5;
        double level = 0.25;
    };

    struct ReverbImpl;

    class Reverb : public Effect {
    public:
        Reverb();
        Reverb(ReverbConfig config);
        virtual ~Reverb();
    
    // internal:
        double render(double sample) override;
        void set_sample_rate(unsigned sample_rate);
    
    private:
        std::unique_ptr<ReverbImpl> impl;
    };
}

#endif // AUDIO_STATION_REVERB_HPP
