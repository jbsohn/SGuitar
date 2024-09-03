//
//  Note.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include "note.hpp"
#include "note_value.hpp"

class NoteImpl final : public Note {
    int midi_note = -1;
public:
    const static std::string note_names_sharp[];
    const static std::string note_names_flat[];

    NoteImpl(const NoteValue note, const int octave) {
        midi_note = (octave + 1) * 12 + static_cast<int>(note);
    }

    explicit NoteImpl(const int midi_note) {
        this->midi_note = midi_note;
    }

    int32_t get_midi_note() override {
        return midi_note;
    }

    NoteValue get_note() override {
        return static_cast<NoteValue>((midi_note / 12) - 1);
    }

    int32_t get_octave() override {
        return midi_note / 12 - 1;
    }

    std::string description() override {
        return note_name_sharp();
    }

    std::string note_name_sharp() override {
        return note_names_sharp[static_cast<int>(get_note())];
    }

    std::string note_name_flat() override {
        return note_names_flat[static_cast<int>(get_note())];
    }
};

const std::string NoteImpl::note_names_sharp[] = {
    "C", "C\u266f",  "D", "D\u266f", "E", "F", "F\u266f", "G",
    "G\u266f", "A", "A\u266f", "B"
};

const std::string NoteImpl::note_names_flat[] = {
    "C", "D\u266d", "D", "E\u266d", "E", "F", "G\u266d",
    "G", "A\u266d", "A", "B\u266d", "B"
};

std::shared_ptr<Note> Note::create_with_note(NoteValue note_value, int32_t octave) {
    return std::make_shared<NoteImpl>(note_value, octave);
}

std::shared_ptr<Note> Note::create_with_midi_note(int32_t midiNote) {
    return std::make_shared<NoteImpl>(midiNote);
}

std::string Note::noteNameSharpForNote(NoteValue note) {
    return NoteImpl::note_names_sharp[static_cast<int>(note)];
}

std::string Note::noteNameFlatForNote(NoteValue note) {
    return NoteImpl::note_names_flat[static_cast<int>(note)];
}
