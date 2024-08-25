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

class ScaleImpl final : public Scale {
protected:
    std::string name;
    std::vector<NoteValue> scaleNoteValues;
public:
    ScaleImpl(const NoteValue rootNoteValue, const std::vector<int>& semitones) {
        const unsigned long numSemitones = semitones.size();
        scaleNoteValues.clear();
        scaleNoteValues.reserve(numSemitones);

        NoteValue curNoteValue = rootNoteValue;
        scaleNoteValues.push_back(rootNoteValue);

        for (const int semitone : semitones) {
            curNoteValue = nextNoteValueInScale(curNoteValue, semitone);
            scaleNoteValues.push_back(curNoteValue);
        }        
    }

    std::vector<NoteValue> get_note_values() override {
        return scaleNoteValues;
    }

    std::string get_description() override {
        static std::string s;
        for (const NoteValue curNoteValue : scaleNoteValues) {
            s += " ";
            s += Note::noteNameSharpForNoteValue(curNoteValue);
            s += " ";
        }
        return s;
    }

protected:
    static NoteValue nextNoteValueInScale(NoteValue noteValue, const int semitone) {
        int curNoteValue = static_cast<int>(noteValue);
        curNoteValue += semitone;

        if (curNoteValue > static_cast<int>(NoteValue::B)) {
            curNoteValue = curNoteValue - (static_cast<int>(NoteValue::B) + 1);
        }
        return static_cast<NoteValue>(curNoteValue);
    }
};

std::shared_ptr<Scale> Scale::create_with_root_note_value(NoteValue root_note_value, const std::vector<int32_t> & semitones) {
    return std::make_shared<ScaleImpl>(root_note_value, semitones);
}
