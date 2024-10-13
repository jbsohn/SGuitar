//
//  Scale.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <format>
#include "note.hpp"
#include "note_value.hpp"
#include "ScaleImpl.hpp"

ScaleImpl::ScaleImpl(const NoteValue root_note, const std::vector<int> &semitones) {
    const auto numSemitones = semitones.size();
    notes.clear();
    notes.reserve(numSemitones);

    auto curNoteValue = root_note;
    notes.push_back(root_note);

    for (const int semitone: semitones) {
        curNoteValue = next_note_in_scale(curNoteValue, semitone);
        notes.push_back(curNoteValue);
    }
}

std::string ScaleImpl::testDescription() {
    std::string s;
    for (const auto curNoteValue: notes) {
        s += std::format("{}", Note::note_name_flat_for_note(curNoteValue));
    }
    return s;
}

NoteValue ScaleImpl::next_note_in_scale(NoteValue note, const int semitone) {
    auto curNoteValue = static_cast<int>(note);
    curNoteValue += semitone;

    if (curNoteValue > static_cast<int>(NoteValue::B)) {
        curNoteValue = curNoteValue - (static_cast<int>(NoteValue::B) + 1);
    }
    return static_cast<NoteValue>(curNoteValue);
}

std::shared_ptr<Scale> Scale::create_with_root_note(NoteValue root_note, const std::vector<int32_t> &semitones) {
    return std::make_shared<ScaleImpl>(root_note, semitones);
}
