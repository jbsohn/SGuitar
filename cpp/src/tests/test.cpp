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
#include "harmonized_scale.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Testing the Note object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    std::cout << "Note: " << note->testDescription() << std::endl;
    std::cout << "Name: " << note->testDescription() << std::endl;
    CHECK(note->get_octave() == 2);
    CHECK(note->get_note() == NoteValue::C);
    CHECK(note->get_midi_note() == 36);

}

TEST_CASE("Testing the Chord object") {
    const auto intervals = {0, 4, 7};
    const auto chord = Chord::create_with_root_note(NoteValue::C, intervals);
    std::cout << "Chord: " << chord->testDescription()  << std::endl;
    CHECK(chord->testDescription() == "CEG");
}

TEST_CASE("Testing the GuitarString object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    const auto guitarString = GuitarString::create_with_start_note(note, 13);
    std::cout << "GuitarString: " << guitarString->testDescription() << std::endl;
    CHECK(guitarString->testDescription() == "CC♯DD♯EFF♯GG♯AA♯BC");

    guitarString->adjust_string_by_steps(2);
    std::cout << "GuitarString: " << guitarString->testDescription() << std::endl;
    CHECK(guitarString->testDescription() == "DD♯EFF♯GG♯AA♯BCC♯D");
}

TEST_CASE("Testing the StringAdjustment object") {
    const auto adjustment = StringAdjustment::create_with_string_number(1, 1);
    std::cout << "StringAdjustment: " << adjustment->testDescription() << std::endl;
    CHECK(adjustment->get_string_number() == 1);
    CHECK(adjustment->get_step() == 1);
}

TEST_CASE("Testing the GuitarAdjustment object") {
    const auto adjustment1 = StringAdjustment::create_with_string_number(1, 1);
    const auto guitarAdjustment = GuitarAdjustment::create_with_adjustment_id("LKL");
    guitarAdjustment->add_string_adjustment(adjustment1);
    std::cout << "guitarAdjustment: " << guitarAdjustment->testDescription() << std::endl;
}

TEST_CASE("Testing the Guitar object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    const auto guitar = Guitar::create();

    guitar->reset_guitar({
        Note::create_with_note(NoteValue::F_SHARP, 4),
        Note::create_with_note(NoteValue::D_SHARP, 4),
        Note::create_with_note(NoteValue::G_SHARP, 4),
        Note::create_with_note(NoteValue::E, 4),
        Note::create_with_note(NoteValue::B, 3),
        Note::create_with_note(NoteValue::G_SHARP, 3),
        Note::create_with_note(NoteValue::F_SHARP, 3),
        Note::create_with_note(NoteValue::E, 3),
        Note::create_with_note(NoteValue::D, 3),
        Note::create_with_note(NoteValue::B, 2)
    },23);

    std::cout << "guitar created:" << std::endl;
    for (const auto strings = guitar->get_strings(); const auto& string : strings) {
        std::cout << string->testDescription() << std::endl;
    }

    const auto guitarAdjustment = GuitarAdjustment::create_with_adjustment_id("LKL");
    const auto stringAdjustment =  StringAdjustment::create_with_string_number(1, 1);
    guitarAdjustment->add_string_adjustment(stringAdjustment);
    guitar->set_adjustment("LKL", guitarAdjustment);

    std::cout << "guitar before:" << std::endl << guitar->testDescription() << std::endl;
    guitar->activate_adjustment("LKL", true);
    std::cout << "guitar after:" << std::endl << guitar->testDescription() << std::endl;
}

TEST_CASE("Testing harmonized scales") {
    auto scale  = HarmonizedScale::create_harmonized_scale_with_root_note(NoteValue::C,
        {2, 2, 1, 2, 2, 2});
    std::cout << scale->testDescription() << std::endl;
}
