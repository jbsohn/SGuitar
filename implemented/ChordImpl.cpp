//
//  Chord.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <vector>
#include <string>
#include <memory>
#include "chord.hpp"
#include "note.hpp"
#include "note_value.hpp"

class ChordImpl : public Chord {
protected:
    std::vector<NoteValue> chordNoteValues;
public:
    ChordImpl(NoteValue rootNoteValue, std::vector<int> intervals) {
        chordNoteValues.clear();
        for (int interval : intervals) {
            NoteValue noteValue = noteValueForInterval(interval, rootNoteValue);
            chordNoteValues.push_back(noteValue);
        }
    }

     std::vector<NoteValue> get_note_values() override {
        return chordNoteValues;
     }

    std::string get_description() override {
        static std::string s = "";
        bool first = true;
        
        for (NoteValue curNoteValue : chordNoteValues) {
            if (!first) { s += " "; }
            s += to_string(curNoteValue);
            first = false;
        }
        return s;
    }

protected:
    NoteValue noteValueForInterval(int interval, NoteValue rootNoteValue) const {
        int value = (int) rootNoteValue + interval;
        if (value > (int) NoteValue::B) {
            value = (value - (int) NoteValue::B) -1;
        }
        return NoteValue(value);
    }
};

std::shared_ptr<Chord> Chord::create_with_root_note_value(NoteValue root_note_value, const std::vector<int32_t> & intervals) {
    return std::make_shared<ChordImpl>(root_note_value, intervals);
}
