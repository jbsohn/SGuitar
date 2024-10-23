//
//  Scale.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <fmt/format.h>
#include "note.hpp"
#include "note_value.hpp"
#include "ScaleImpl.hpp"

ScaleImpl::ScaleImpl(const NoteValue root_note, const std::vector<int>& semitones) {
    const auto num_semitones = semitones.size();
    notes.clear();
    notes.reserve(num_semitones);
    auto cur_note_value = root_note;
    notes.push_back(root_note);
    for (const int semitone : semitones) {
        cur_note_value = next_note_in_scale(cur_note_value, semitone);
        notes.push_back(cur_note_value);
    }
}

std::string ScaleImpl::test_description() {
    std::string s;
    for (const auto curNoteValue : notes) {
        s += fmt::format("{}", Note::note_name_flat_for_note(curNoteValue));
    }
    return s;
}

NoteValue ScaleImpl::next_note_in_scale(NoteValue note, const int semitone) {
    auto cur_note_value = static_cast<int>(note);
    cur_note_value += semitone;
    if (cur_note_value > static_cast<int>(NoteValue::B)) {
        cur_note_value = cur_note_value - (static_cast<int>(NoteValue::B) + 1);
    }
    return static_cast<NoteValue>(cur_note_value);
}

std::shared_ptr<Scale> Scale::create_with_root_note(NoteValue root_note, const std::vector<int32_t>& semitones) {
    return std::make_shared<ScaleImpl>(root_note, semitones);
}
