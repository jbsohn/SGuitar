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
#include "note_value.hpp"

class ChordImpl final : public Chord {
protected:
    std::vector<NoteValue> chordNoteValues;
public:
    ChordImpl(const NoteValue rootNoteValue, const std::vector<int>& intervals) {
        chordNoteValues.clear();
        for (const int interval : intervals) {
            NoteValue noteValue = noteValueForInterval(interval, rootNoteValue);
            chordNoteValues.push_back(noteValue);
        }
    }

     std::vector<NoteValue> get_note_values() override {
        return chordNoteValues;
     }

    std::string get_description() override {
        static std::string s;
        bool first = true;
        
        for (const NoteValue curNoteValue : chordNoteValues) {
            if (!first) { s += " "; }
            s += to_string(curNoteValue);
            first = false;
        }
        return s;
    }

protected:
    static NoteValue noteValueForInterval(const int interval, NoteValue rootNoteValue) {
        int value = static_cast<int>(rootNoteValue) + interval;
        if (value > static_cast<int>(NoteValue::B)) {
            value = value - static_cast<int>(NoteValue::B) -1;
        }
        return static_cast<NoteValue>(value);
    }
};

std::shared_ptr<Chord> Chord::create_with_root_note_value(NoteValue root_note_value, const std::vector<int32_t> & intervals) {
    return std::make_shared<ChordImpl>(root_note_value, intervals);
}
