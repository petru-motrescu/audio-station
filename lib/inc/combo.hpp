#ifndef AUDIO_STATION_COMBO_HPP
#define AUDIO_STATION_COMBO_HPP

#include <vector>
#include "instrument.hpp"
#include "note.hpp"

namespace audiostation {

    class Combo : public Instrument {
    public:
        Combo();
        Combo(std::vector<Instrument*> instruments);
        virtual ~Combo();
        
        void trigger(Note note) override;
        void release(Note note) override;
        AudioSample render() override;
    
    private:
        std::vector<Instrument*> instruments;
    };
}

#endif // AUDIO_STATION_COMBO_HPP
