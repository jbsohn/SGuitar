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
    int midiValue = -1;
public:
    const static std::string note_names_sharp[];
    const static std::string note_names_flat[];

    NoteImpl(const NoteValue note, const int pitch) {
        midiValue = pitch * 12 + static_cast<int>(note);
    }

    explicit NoteImpl(const int midi_note) {
        this->midiValue = midi_note;
    }

    int32_t get_midi_note() override {
        return midiValue;
    }

    NoteValue get_note() override {
        return static_cast<NoteValue>((midiValue - 12) % 12);
    }

    int32_t get_pitch() override {
        if (midiValue >= 0) {
            return midiValue / 12;
        }
        return -1;
    }

    std::string description() override {
        const std::string name = note_name_sharp();
        const auto pitch = get_pitch();
        std::string namePitch = name + "-" + std::to_string(pitch);
        return namePitch;
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

std::shared_ptr<Note> Note::create_with_note(NoteValue note_value, int32_t pitch) {
    return std::make_shared<NoteImpl>(note_value, pitch);
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
