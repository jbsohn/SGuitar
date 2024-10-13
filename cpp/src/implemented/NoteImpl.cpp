//
//  Note.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include "NoteImpl.hpp"

const std::string NoteImpl::note_names_sharp[] = {
    "C", "C\u266f", "D", "D\u266f", "E", "F", "F\u266f", "G",
    "G\u266f", "A", "A\u266f", "B"
};

const std::string NoteImpl::note_names_flat[] = {
    "C", "D\u266d", "D", "E\u266d", "E", "F", "G\u266d",
    "G", "A\u266d", "A", "B\u266d", "B"
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
