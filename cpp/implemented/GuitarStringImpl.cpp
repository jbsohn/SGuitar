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
    std::shared_ptr<Note> start_note;
    int number_of_fret;
public:
    GuitarStringImpl() {
        number_of_fret = 0;
    }

    GuitarStringImpl(const std::shared_ptr<Note>& start_note, const int number_of_frets) {
        notes.resize(number_of_frets);
        this->start_note = start_note;
        this->number_of_fret = number_of_frets;
        reset();
    }

    std::shared_ptr<Note> get_start_note() override {
        return start_note;
    }

    std::vector<std::shared_ptr<Note>> get_notes() override {
            return notes;
    }

    void reset() override {
        int note = start_note->get_midi_note();
        for (int fret = 0; fret < number_of_fret; fret++) {

            notes[fret] = Note::create_with_midi_note(note);
            note++;
        }
    }

    void adjust_string_by_steps(const int32_t steps) override {
        for (int fret = 0; fret < number_of_fret; fret++) {
            int note = notes[fret]->get_midi_note();
            note += steps;
            notes[fret] = Note::create_with_midi_note(note);
        }
    }

    std::string description() override {
        std::string s;
        for (const std::shared_ptr<Note>& note : notes) {
            s += note->description();
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
