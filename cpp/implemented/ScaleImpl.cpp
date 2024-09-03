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
    std::string name;
    std::vector<NoteValue> notes;
public:
    ScaleImpl(const NoteValue root_note, const std::vector<int>& semitones) {
        const auto numSemitones = semitones.size();
        notes.clear();
        notes.reserve(numSemitones);

        auto curNoteValue = root_note;
        notes.push_back(root_note);

        for (const int semitone : semitones) {
            curNoteValue = next_note_in_scale(curNoteValue, semitone);
            notes.push_back(curNoteValue);
        }        
    }

    std::vector<NoteValue> get_notes() override {
        return notes;
    }

    std::string description() override {
        std::string s;
        for (const auto curNoteValue : notes) {
            s += Note::noteNameSharpForNote(curNoteValue);
        }
        return s;
    }

protected:
    static NoteValue next_note_in_scale(NoteValue note, const int semitone) {
        auto curNoteValue = static_cast<int>(note);
        curNoteValue += semitone;

        if (curNoteValue > static_cast<int>(NoteValue::B)) {
            curNoteValue = curNoteValue - (static_cast<int>(NoteValue::B) + 1);
        }
        return static_cast<NoteValue>(curNoteValue);
    }
};

std::shared_ptr<Scale> Scale::create_with_root_note(NoteValue root_note, const std::vector<int32_t> & semitones) {
    return std::make_shared<ScaleImpl>(root_note, semitones);
}
