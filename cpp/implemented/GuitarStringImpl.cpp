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
    std::vector<std::shared_ptr<Note> > notes;
    std::shared_ptr<Note> start_note;
    int number_of_fret;

public:
    GuitarStringImpl() {
        number_of_fret = 0;
        notes = {};
    }

    GuitarStringImpl(const std::shared_ptr<Note> &start_note, const int number_of_frets) {
        this->start_note = start_note;
        this->number_of_fret = number_of_frets;
        this->notes = string_with_start_note(start_note->get_midi_note(), number_of_frets);
    }

    std::shared_ptr<Note> get_start_note() override {
        return start_note;
    }

    std::vector<std::shared_ptr<Note> > get_notes() override {
        return notes;
    }

    void adjust_string_by_steps(const int32_t steps) override {
        const auto start_note_midi = notes[0]->get_midi_note() + steps;
        auto notes = string_with_start_note(start_note_midi, number_of_fret);
        this->notes = notes;
    }

    void reset() override {
        notes = string_with_start_note(start_note->get_midi_note(), number_of_fret);
    }

    std::string description() override {
        std::string s;
        for (const std::shared_ptr<Note> &note: notes) {
            s += note->description();
        }
        return s;
    }

protected:
    static std::vector<std::shared_ptr<Note> > string_with_start_note(const int midi_start_node,
                                                                      const int number_of_frets) {
        auto notes = std::vector<std::shared_ptr<Note> >();
        auto cur_midi_value = midi_start_node;
        for (int i = 0; i < number_of_frets; i++) {
            notes.push_back(Note::create_with_midi_note(cur_midi_value));
            cur_midi_value++;
        }
        return notes;
    }
};

std::shared_ptr<GuitarString> GuitarString::create() {
    return std::make_shared<GuitarStringImpl>();
}

/*not-null*/
std::shared_ptr<GuitarString> GuitarString::create_with_start_note(const /*not-null*/ std::shared_ptr<Note> &start_note,
                                                                   int32_t number_of_frets) {
    return std::make_shared<GuitarStringImpl>(start_note, number_of_frets);
}
