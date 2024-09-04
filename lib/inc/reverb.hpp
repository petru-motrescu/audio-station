#ifndef AUDIO_STATION_REVERB_HPP
#define AUDIO_STATION_REVERB_HPP

#include <memory>
#include "audio-sample.hpp"
#include "effect.hpp"

namespace audiostation {

    enum class ReverbAlgo {
        PRIMES
    };

    struct ReverbConfig {
        double size = 0.5;
        double level = 0.25;
        ReverbAlgo algo = ReverbAlgo::PRIMES;
    };

    struct ReverbImpl;

    class Reverb : public Effect {
    public:
        Reverb();
        Reverb(ReverbConfig config);
        virtual ~Reverb();

        AudioSample render(AudioSample sample) override;
        void set_sample_rate(unsigned sample_rate);
    
    private:
        std::unique_ptr<ReverbImpl> impl;
    };
}

#endif // AUDIO_STATION_REVERB_HPP
