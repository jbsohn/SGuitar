//
//  GuitarString.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <memory>
#include <vector>
#include <string>
#include "guitar_string.hpp"
#include "note.hpp"

class NoteImpl;

class GuitarStringImpl final : public GuitarString {
    std::vector<std::shared_ptr<Note>> notes;
    std::shared_ptr<Note> startNote;
    int numberOfFrets;
public:
    GuitarStringImpl() {
        numberOfFrets = 0;
    }

    GuitarStringImpl(const std::shared_ptr<Note>& startNote, const int numberOfFrets) {
        notes.resize(numberOfFrets);
        this->startNote = startNote;
        this->numberOfFrets = numberOfFrets;
        reset();
    }

    std::shared_ptr<Note> get_start_note() override {
        return startNote;
    }

    std::vector<std::shared_ptr<Note>> get_notes() override {
            return notes;
    }

    void reset() override {
        int curNoteMIDIValue = startNote->get_midi_value();
        for (int fret = 0; fret < numberOfFrets; fret++) {

            notes[fret] = Note::create_with_midi_value(curNoteMIDIValue);
            curNoteMIDIValue++;
        }
    }

    void adjust_string_by_steps(const int32_t steps) override {
        for (int fret = 0; fret < numberOfFrets; fret++) {
            int curNoteMIDIValue = notes[fret]->get_midi_value();
            curNoteMIDIValue += steps;
            notes[fret] = Note::create_with_midi_value(curNoteMIDIValue);
        }
    }

    std::string get_description() override {
        std::string s;
        for (const std::shared_ptr<Note>& note : notes) {
            s += note->get_description();
            s += " ";
        }
        return s;
    }
};

std::shared_ptr<GuitarString> GuitarString::create() {
    return std::make_shared<GuitarStringImpl>();
}

/*not-null*/
std::shared_ptr<GuitarString> GuitarString::create_with_start_note(const /*not-null*/ std::shared_ptr<Note> & start_note, int32_t number_of_frets) {
    return std::make_shared<GuitarStringImpl>(start_note, number_of_frets);
}
