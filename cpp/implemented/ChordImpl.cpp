//
//  Chord.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <vector>
#include <string>
#include "note.hpp"
#include "chord.hpp"
#include "note_value.hpp"

class ChordImpl final : public Chord {
    std::vector<NoteValue> notes;
public:
    ChordImpl(const NoteValue root_note, const std::vector<int>& intervals) {
        for (const int interval : intervals) {
            auto note = note_for_interval(interval, root_note);
            notes.push_back(note);
        }
    }

     std::vector<NoteValue> get_notes() override {
        return notes;
     }

    std::string description() override {
        std::string s;
        for (const NoteValue note : notes) {
            s += Note::note_name_sharp_for_note(note);
        }
        return s;
    }
protected:
    static NoteValue note_for_interval(const int interval, NoteValue rootNote) {
        auto value = static_cast<int>(rootNote) + interval;
        if (value > static_cast<int>(NoteValue::B)) {
            value = value - static_cast<int>(NoteValue::B) -1;
        }
        return static_cast<NoteValue>(value);
    }
};

std::shared_ptr<Chord> Chord::create_with_root_note(NoteValue root_note, const std::vector<int32_t> & intervals) {
    return std::make_shared<ChordImpl>(root_note, intervals);
}
