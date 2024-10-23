//
//  GuitarString.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <fmt/format.h>
#include <vector>
#include <string>
#include "GuitarStringImpl.hpp"

GuitarStringImpl::GuitarStringImpl() {
    number_of_fret = 0;
    notes = {};
}

GuitarStringImpl::GuitarStringImpl(const std::shared_ptr<Note>& start_note, const int number_of_frets) {
    this->start_note = start_note;
    this->number_of_fret = number_of_frets;
    this->notes = string_with_start_note(start_note->get_midi_note(), number_of_frets);
}

void GuitarStringImpl::adjust_string_by_steps(const int32_t steps) {
    const auto start_note_midi = notes[0]->get_midi_note() + steps;
    const auto notes = string_with_start_note(start_note_midi, number_of_fret);
    this->notes = notes;
}

std::string GuitarStringImpl::test_description() {
    std::string s;
    for (const std::shared_ptr<Note>& note : notes) {
        s += fmt::format("{}", note->test_description());
    }
    return s;
}

std::vector<std::shared_ptr<Note>> GuitarStringImpl::string_with_start_note(const int midi_start_node,
                                                                            const int number_of_frets) {
    auto notes = std::vector<std::shared_ptr<Note>>();
    auto cur_midi_value = midi_start_node;
    for (int i = 0; i < number_of_frets; i++) {
        notes.push_back(Note::create_with_midi_note(cur_midi_value));
        cur_midi_value++;
    }
    return notes;
}

std::shared_ptr<GuitarString> GuitarString::create() {
    return std::make_shared<GuitarStringImpl>();
}

/*not-null*/
std::shared_ptr<GuitarString> GuitarString::create_with_start_note(const std::shared_ptr<Note>& start_note,
                                                                   int32_t number_of_frets) {
    return std::make_shared<GuitarStringImpl>(start_note, number_of_frets);
}
