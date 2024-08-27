//
//  SGuitarTest
//
//  Created by John Sohn on 8/18/24.
//

#include <iostream>
#include "note_value.hpp"
#include "string_adjustment.hpp"
#include "note.hpp"
#include "scale.hpp"
#include "chord.hpp"
#include "guitar_string.hpp"
#include "guitar_adjustment.hpp"
#include "guitar.hpp"

void testNote() {
    const std::shared_ptr<Note> note = Note::create_with_note_value(NoteValue::C, 2);
    std::cout << "Note: " << note->get_description() << std::endl;
    std::cout << "Name: " << note->get_description() << std::endl;
}

void testScale() {
    const auto semitones = {2, 2, 1, 2, 2, 2};
    const auto scale = Scale::create_with_root_note_value(NoteValue::C, semitones);
    std::cout << "Scale: " << scale->get_description() << std::endl;
}

void testChord() {
    const auto intervals = {0, 4, 7};
    const auto chord = Chord::create_with_root_note_value(NoteValue::C, intervals);
    std::cout << "Chord: " << chord->get_description()  << std::endl;
}

void testGuitarString() {
    const std::shared_ptr<Note> note = Note::create_with_note_value(NoteValue::C, 2);
    const auto guitarString = GuitarString::create_with_midi_start_value(note->get_midi_value(), 13);
    std::cout << "GuitarString: " << guitarString->get_description() << std::endl;
    guitarString->adjust_string_by_steps(2);
    std::cout << "GuitarString: " << guitarString->get_description() << std::endl;
}

void testStringAdjustment() {
    const auto adjustment = StringAdjustment::create_with_string_number(1, 1);
    std::cout << "StringAdjustment: " << adjustment->get_description() << std::endl;
}

void testGuitarAdjustment() {
    const auto adjustment1 = StringAdjustment::create_with_string_number(1, 1);

    const auto guitarAdjustment = GuitarAdjustment::create_with_adjustment_id("LKL");
    guitarAdjustment->add_string_adjustment(adjustment1);
    std::cout << "guitarAdjustment: " << guitarAdjustment->get_description() << std::endl;
}

void testGuitar() {
    const std::shared_ptr<Note> note = Note::create_with_note_value(NoteValue::C, 2);
    const auto guitar = Guitar::create();

    guitar->reset_guitar({
        Note::create_with_note_value(NoteValue::F_SHARP, 4),
        Note::create_with_note_value(NoteValue::D_SHARP, 4),
        Note::create_with_note_value(NoteValue::G_SHARP, 4),
        Note::create_with_note_value(NoteValue::E, 4),
        Note::create_with_note_value(NoteValue::B, 3),
        Note::create_with_note_value(NoteValue::G_SHARP, 3),
        Note::create_with_note_value(NoteValue::F_SHARP, 3),
        Note::create_with_note_value(NoteValue::E, 3),
        Note::create_with_note_value(NoteValue::D, 3),
        Note::create_with_note_value(NoteValue::B, 2)
    },23);

    std::cout << "guitar created:" << std::endl;
    for (const auto strings = guitar->get_strings(); const auto& string : strings) {
        std::cout << string->get_description() << std::endl;
    }

    const auto guitarAdjustment = GuitarAdjustment::create_with_adjustment_id("LKL");
    const auto stringAdjustment =  StringAdjustment::create_with_string_number(1, 1);
    guitarAdjustment->add_string_adjustment(stringAdjustment);
    guitar->set_adjustment("LKL", guitarAdjustment);

    std::cout << "guitar before:" << std::endl << guitar->get_description() << std::endl;
    guitar->activate_adjustment("LKL", true);
    std::cout << "guitar after:" << std::endl << guitar->get_description() << std::endl;
}

int main(int argc, const char * argv[]) {
    testNote();
    testScale();
    testChord();
    testStringAdjustment();
    testGuitarAdjustment();
    testChord();
    testGuitar();
    return 0;
}
