#ifndef AUDIO_STATION_NOTE_HPP
#define AUDIO_STATION_NOTE_HPP

#include <vector>

namespace audiostation {

    enum class Note {
        A0, AB0, B0,
        C1, CD1, D1, DE1, E1, F1, FG1, G1, GA1, A1, AB1, B1,
        C2, CD2, D2, DE2, E2, F2, FG2, G2, GA2, A2, AB2, B2,
        C3, CD3, D3, DE3, E3, F3, FG3, G3, GA3, A3, AB3, B3,
        C4, CD4, D4, DE4, E4, F4, FG4, G4, GA4, A4, AB4, B4,
        C5, CD5, D5, DE5, E5, F5, FG5, G5, GA5, A5, AB5, B5,
        C6, CD6, D6, DE6, E6, F6, FG6, G6, GA6, A6, AB6, B6,
        C7, CD7, D7, DE7, E7, F7, FG7, G7, GA7, A7, AB7, B7,
        C8
    };

    struct Notes {
        static const std::vector<Note> piano_notes;
        
        static double get_frequency(Note note);
        static inline int to_int(Note note) { return static_cast<int>(note); }
        static inline Note from_int(int note) { return static_cast<Note>(note); }
    };
}

#endif // AUDIO_STATION_NOTE_HPP