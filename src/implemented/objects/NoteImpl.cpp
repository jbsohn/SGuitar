//
//  Note.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include <format>
#include "NoteImpl.hpp"

const std::string NoteImpl::note_names_sharp[] = {
    "C",
    "C♯",
    "D",
    "D♯",
    "E",
    "F",
    "F♯",
    "G",
    "G♯",
    "A",
    "A♯",
    "B"
};

const std::string NoteImpl::note_names_flat[] = {
    "C",
    "D♭",
    "D",
    "E♭",
    "E",
    "F",
    "G♭",
    "G",
    "A♭",
    "A",
    "B♭",
    "B"
};

std::shared_ptr<Note> Note::create_with_note(NoteValue note, int32_t octave) {
    return std::make_shared<NoteImpl>(note, octave);
}

std::shared_ptr<Note> Note::create_with_midi_note(int32_t midi_note) {
    return std::make_shared<NoteImpl>(midi_note);
}

std::string Note::note_name_sharp_for_note(NoteValue note) {
    return NoteImpl::note_names_sharp[static_cast<int>(note)];
}

std::string Note::note_name_flat_for_note(NoteValue note) {
    return NoteImpl::note_names_flat[static_cast<int>(note)];
}

NoteValue Note::note_value_for_note_string(const std::string& note_string) {
    for (int i = 0; const auto& name : NoteImpl::note_names_sharp) {
        if (name == note_string) {
            return static_cast<NoteValue>(i);
        }
        i++;
    }
    for (int i = 0; const auto& name : NoteImpl::note_names_flat) {
        if (name == note_string) {
            return static_cast<NoteValue>(i);
        }
        i++;
    }
    return static_cast<NoteValue>(0);
}
