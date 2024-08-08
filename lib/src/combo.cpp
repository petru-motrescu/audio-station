#include <iostream>
#include "combo.hpp"
using namespace audiostation;

Combo::Combo() { }

Combo::Combo(std::vector<Instrument*> instruments) {
    this->instruments = instruments;
}

Combo::~Combo() {
    this->instruments.clear();
}

void Combo::trigger(Note note) {
    for (auto& instrument : this->instruments) {
        instrument->trigger(note);
    }
}

void Combo::release(Note note) {
    for (auto& instrument : this->instruments) {
        instrument->release(note);
    }
}

double Combo::render() {
    double sample = 0;
    
    for (auto& instrument : this->instruments) {
        sample += instrument->render();
    }

    return sample;
}
