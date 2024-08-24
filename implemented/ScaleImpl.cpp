//
//  Scale.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <vector>
#include <string>
#include "scale.hpp"
#include "note.hpp"
#include "note_value.hpp"

class ScaleImpl : public Scale {
protected:
    std::string name;
    std::vector<NoteValue> scaleNoteValues;
public:
    ScaleImpl(NoteValue rootNoteValue, std::vector<int> semitones) {
        unsigned long numSemitones = semitones.size();
        scaleNoteValues.clear();
        scaleNoteValues.reserve(numSemitones);

        NoteValue curNoteValue = rootNoteValue;
        scaleNoteValues.push_back(rootNoteValue);

        for (int semitone : semitones) {
            curNoteValue = nextNoteValueInScale(curNoteValue, semitone);
            scaleNoteValues.push_back(curNoteValue);
        }        
    }

    std::vector<NoteValue> get_note_values() override {
        return scaleNoteValues;
    }

    std::string get_description() override {
        static std::string s;
        
        s = "";
        bool first = true;
        
        for (NoteValue curNoteValue : scaleNoteValues) {
            if (!first) {
                s += " ";
            }
            //s += NoteName::nameForNoteValue(curNoteValue, AT_SHARP);
            first = false;
        }
        return s;
    }

protected:
    NoteValue nextNoteValueInScale(NoteValue noteValue, int semitone) const {
        int curNoteValue = (int) noteValue;
        curNoteValue += semitone;

        if (curNoteValue > (int) NoteValue::B) {
            curNoteValue = curNoteValue - ((int) NoteValue::B + 1);
        }
        return (NoteValue) curNoteValue;
    }
};

std::shared_ptr<Scale> Scale::create_with_root_note_value(NoteValue root_note_value, const std::vector<int32_t> & semitones) {
    return std::make_shared<ScaleImpl>(root_note_value, semitones);
}
