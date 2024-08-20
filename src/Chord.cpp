//
//  Chord.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <vector>
#include <string>
#include "SG/Chord.hpp"
#include "SG/Note.hpp"
#include "SG/NoteName.hpp"

namespace SG {
    Chord::Chord(int rootNoteValue, std::vector<int> intervals) {
        chordNoteValues.clear();
        for (int interval : intervals) {
            int noteValue = noteValueForInterval(interval, rootNoteValue);
            chordNoteValues.push_back(noteValue);
        }
    }

    bool Chord::isNoteValueInChord(int noteValue) const {
        for (int curNoteValue : chordNoteValues) {
            if (curNoteValue == noteValue) {
                return true;
            }
        }
        return false;
    }

    std::string Chord::getDescription() {
        static std::string s;

        s = "";
        bool first = true;
        
        for (int curNoteValue : chordNoteValues) {
            if (!first) {
                s += " ";
            }
            s += NoteName::nameForNoteValue(curNoteValue, AT_SHARP);
            first = false;
        }
        
        return s;
    }
    
    void Chord::init(const Chord& chord) {
        chordNoteValues = chord.chordNoteValues;
    }
    
    int Chord::noteValueForInterval(int interval, int rootNoteValue) const {
        int value = rootNoteValue + interval;
        
        if (value > NOTE_VALUE_B) {
            value = (value - NOTE_VALUE_B) -1;
        }
        return (int) value;
    }
}
