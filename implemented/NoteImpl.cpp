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
    int midiValue{};
public:
    NoteImpl(const int noteValue, const int pitch) {
        init(noteValue, pitch);
    }

    explicit NoteImpl(const int midiValue) {
        this->midiValue = midiValue;
    }

    explicit NoteImpl(const std::string &name) {
        this->midiValue = -1;
        const std::string& n = name;
        const std::string delimiter = "-";

        size_t dashPos = n.find(delimiter);
        constexpr int noteValue =-1;
        int pitch = -1;

        if (dashPos == std::string::npos) {
            return;
        }

        std::string noteName = n.substr(0, dashPos);
        std::string notePitch = n.substr(dashPos + 1, std::string::npos);
        // FIXME: noteValue = NoteName::noteValueForName(noteName);

        try {
            pitch = std::stoi(notePitch);
        } catch (...) {
            return;
        }

        init(noteValue, pitch);
    }

    void init(const int noteValue, const int pitch) {
        midiValue = ((pitch * 12) + noteValue);
    }

    int32_t get_midi_value() override {
        return midiValue;
    }

    int32_t get_note_value() override {
        int value = (midiValue -12) % 12;
        return (int)value;    }

    int32_t get_pitch_value() override {
        if (midiValue >= 0) {
            int value = midiValue / 12;
            return value;
        }
        return -1;
    }

    std::string get_note_name_pitch_utf8() override {
        //std::string name = NoteName::getNoteNameSharpUTF8(getNoteValue());
        const int pitch = get_pitch_value();

        std::string namePitch = "note: " + std::to_string(get_note_value()) + ", pitch: " + std::to_string(pitch);
        return namePitch;
    }
};

std::shared_ptr<Note> Note::create_with_note_value(int32_t note_value, int32_t pitch) {
    return std::make_shared<NoteImpl>(note_value, pitch);
}

std::shared_ptr<Note> Note::create_with_midi_value(int32_t midiValue) {
    return std::make_shared<NoteImpl>(midiValue);
}

std::shared_ptr<Note> Note::create_with_name(const std::string & name) {
    return std::make_shared<NoteImpl>(name);
}
