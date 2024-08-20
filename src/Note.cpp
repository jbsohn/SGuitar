//
//  Note.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include "SG/Note.hpp"
#include "SG/NoteName.hpp"

namespace SG {
    Note::Note() {
        midiValue = -1;
    }

    Note::Note(int noteValue, int pitch) {
        init(noteValue, pitch);
    }

    Note::Note(int midiValue) {
        this->midiValue = midiValue;
    }

    Note::Note(std::string name) {
        this->midiValue = -1;
        std::string n = name;
        std::string delimiter = "-";

        size_t dashPos = n.find(delimiter);
        int noteValue = NOTE_VALUE_NONE;
        int pitch = -1;

        if (dashPos == std::string::npos) {
            return;
        }

        std::string noteName = n.substr(0, dashPos);
        std::string notePitch = n.substr(dashPos + 1, std::string::npos);
        noteValue = NoteName::noteValueForName(noteName);

        try {
            pitch = std::stoi(notePitch);
        } catch (...) {
            return;
        }

        init(noteValue, pitch);
    }

    int Note::getMIDIValue() const {
        return midiValue;
    }

    int Note::getNoteValue() const {
        int value = (midiValue -12) % 12;
        return (int)value;
    }

    int Note::getPitchValue() const {
        if (midiValue >= 0) {
            int value = midiValue / 12;
            return value;
        }
        return -1;
    }
    
    std::string Note::getNoteNamePitchUTF8() const {
        std::string name = NoteName::getNoteNameSharpUTF8(getNoteValue());
        int pitch = getPitchValue();
        std::string namePitch = name + "-" + std::to_string(pitch);
        return namePitch;
    }
    
    void Note::init(int noteValue, int pitch) {
        midiValue = ((pitch * 12) + noteValue);
    }
}
