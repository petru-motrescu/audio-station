#include <iostream>
#include "note.hpp"
#include "frequency.hpp"
using namespace audiostation;

double audiostation::Notes::get_frequency(Note note) {
    switch (note) {
        case Note::A0: return Frequency::A0;
        case Note::AB0: return Frequency::AB0;
        case Note::B0: return Frequency::B0;
        // ---
        case Note::C1: return Frequency::C1;
        case Note::CD1: return Frequency::CD1;
        case Note::D1: return Frequency::D1;
        case Note::DE1: return Frequency::DE1;
        case Note::E1: return Frequency::E1;
        case Note::F1: return Frequency::F1;
        case Note::FG1: return Frequency::FG1;
        case Note::G1: return Frequency::G1;
        case Note::GA1: return Frequency::GA1;
        case Note::A1: return Frequency::A1;
        case Note::AB1: return Frequency::AB1;
        case Note::B1: return Frequency::B1;
        // ---
        case Note::C2: return Frequency::C2;
        case Note::CD2: return Frequency::CD2;
        case Note::D2: return Frequency::D2;
        case Note::DE2: return Frequency::DE2;
        case Note::E2: return Frequency::E2;
        case Note::F2: return Frequency::F2;
        case Note::FG2: return Frequency::FG2;
        case Note::G2: return Frequency::G2;
        case Note::GA2: return Frequency::GA2;
        case Note::A2: return Frequency::A2;
        case Note::AB2: return Frequency::AB2;
        case Note::B2: return Frequency::B2;
        // ---
        case Note::C3: return Frequency::C3;
        case Note::CD3: return Frequency::CD3;
        case Note::D3: return Frequency::D3;
        case Note::DE3: return Frequency::DE3;
        case Note::E3: return Frequency::E3;
        case Note::F3: return Frequency::F3;
        case Note::FG3: return Frequency::FG3;
        case Note::G3: return Frequency::G3;
        case Note::GA3: return Frequency::GA3;
        case Note::A3: return Frequency::A3;
        case Note::AB3: return Frequency::AB3;
        case Note::B3: return Frequency::B3;
        // ---
        case Note::C4: return Frequency::C4;
        case Note::CD4: return Frequency::CD4;
        case Note::D4: return Frequency::D4;
        case Note::DE4: return Frequency::DE4;
        case Note::E4: return Frequency::E4;
        case Note::F4: return Frequency::F4;
        case Note::FG4: return Frequency::FG4;
        case Note::G4: return Frequency::G4;
        case Note::GA4: return Frequency::GA4;
        case Note::A4: return Frequency::A4;
        case Note::AB4: return Frequency::AB4;
        case Note::B4: return Frequency::B4;
        // ---
        case Note::C5: return Frequency::C5;
        case Note::CD5: return Frequency::CD5;
        case Note::D5: return Frequency::D5;
        case Note::DE5: return Frequency::DE5;
        case Note::E5: return Frequency::E5;
        case Note::F5: return Frequency::F5;
        case Note::FG5: return Frequency::FG5;
        case Note::G5: return Frequency::G5;
        case Note::GA5: return Frequency::GA5;
        case Note::A5: return Frequency::A5;
        case Note::AB5: return Frequency::AB5;
        case Note::B5: return Frequency::B5;
        // ---
        case Note::C6: return Frequency::C6;
        case Note::CD6: return Frequency::CD6;
        case Note::D6: return Frequency::D6;
        case Note::DE6: return Frequency::DE6;
        case Note::E6: return Frequency::E6;
        case Note::F6: return Frequency::F6;
        case Note::FG6: return Frequency::FG6;
        case Note::G6: return Frequency::G6;
        case Note::GA6: return Frequency::GA6;
        case Note::A6: return Frequency::A6;
        case Note::AB6: return Frequency::AB6;
        case Note::B6: return Frequency::B6;
        // ---
        case Note::C7: return Frequency::C7;
        case Note::CD7: return Frequency::CD7;
        case Note::D7: return Frequency::D7;
        case Note::DE7: return Frequency::DE7;
        case Note::E7: return Frequency::E7;
        case Note::F7: return Frequency::F7;
        case Note::FG7: return Frequency::FG7;
        case Note::G7: return Frequency::G7;
        case Note::GA7: return Frequency::GA7;
        case Note::A7: return Frequency::A7;
        case Note::AB7: return Frequency::AB7;
        case Note::B7: return Frequency::B7;
        // ---
        case Note::C8: return Frequency::C8;
    }
}