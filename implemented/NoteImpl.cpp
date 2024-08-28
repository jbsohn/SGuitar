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
protected:
    int midiValue = -1;
public:
    const static std::string noteNamesSharp[];
    const static std::string noteNamesFlat[];

    NoteImpl(const NoteValue noteValue, const int pitch) {
        midiValue = pitch * 12 + static_cast<int>(noteValue);
    }

    explicit NoteImpl(const int midiValue) {
        this->midiValue = midiValue;
    }

    int32_t get_midi_value() override {
        return midiValue;
    }

    NoteValue get_note_value() override {
        return static_cast<NoteValue>((midiValue - 12) % 12);
    }

    int32_t get_pitch_value() override {
        if (midiValue >= 0) {
            return midiValue / 12;
        }
        return -1;
    }

    std::string get_description() override {
        const std::string name = note_name_sharp();
        const auto pitch = get_pitch_value();
        std::string namePitch = name + "-" + std::to_string(pitch);
        return namePitch;
    }

    std::string note_name_sharp() override {
        return noteNamesSharp[static_cast<int>(get_note_value())];
    }

    std::string note_name_flat() override {
        return noteNamesFlat[static_cast<int>(get_note_value())];
    }
};

const std::string NoteImpl::noteNamesSharp[] = {
    "C", "C\u266f",  "D", "D\u266f", "E", "F", "F\u266f", "G",
    "G\u266f", "A", "A\u266f", "B"
};

const std::string NoteImpl::noteNamesFlat[] = {
    "C", "D\u266d", "D", "E\u266d", "E", "F", "G\u266d",
    "G", "A\u266d", "A", "B\u266d", "B"
};

std::shared_ptr<Note> Note::create_with_note_value(NoteValue note_value, int32_t pitch) {
    return std::make_shared<NoteImpl>(note_value, pitch);
}

std::shared_ptr<Note> Note::create_with_midi_value(int32_t midiValue) {
    return std::make_shared<NoteImpl>(midiValue);
}

std::string Note::noteNameSharpForNoteValue(NoteValue note_value) {
    return NoteImpl::noteNamesSharp[static_cast<int>(note_value)];
}

std::string Note::noteNameFlatForNoteValue(NoteValue note_value) {
    return NoteImpl::noteNamesFlat[static_cast<int>(note_value)];
}
