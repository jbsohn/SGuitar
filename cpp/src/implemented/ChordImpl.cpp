//
//  Chord.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <format>
#include <vector>
#include <string>
#include "ChordImpl.hpp"

ChordImpl::ChordImpl(const NoteValue root_note, const std::vector<int> &intervals) {
    for (const int interval: intervals) {
        auto note = note_for_interval(interval, root_note);
        notes.push_back(note);
    }
}

std::string ChordImpl::testDescription() {
    std::string s;
    for (const NoteValue note: notes) {
        s += std::format("{}", Note::note_name_flat_for_note(note));
    }
    return s;
}

NoteValue ChordImpl::note_for_interval(const int interval, NoteValue rootNote) {
    auto value = static_cast<int>(rootNote) + interval;
    if (value > static_cast<int>(NoteValue::B)) {
        value = value - static_cast<int>(NoteValue::B) - 1;
    }
    return static_cast<NoteValue>(value);
}

std::shared_ptr<Chord> Chord::create_with_root_note(NoteValue root_note, const std::vector<int32_t> &intervals) {
    return std::make_shared<ChordImpl>(root_note, intervals);
}

std::shared_ptr<Chord> Chord::create_with_notes(const std::vector<NoteValue> &notes) {
    return std::make_shared<ChordImpl>(notes);
}
