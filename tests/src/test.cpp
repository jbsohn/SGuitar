//
//  SGuitarTest
//
//  Created by John Sohn on 8/18/24.
//
#include <iostream>
#include <vector>
#include "chord.hpp"
#include "guitar.hpp"
#include "guitar_adjustment.hpp"
#include "guitar_string.hpp"
#include "harmonized_scale.hpp"
#include "note.hpp"
#include "note_value.hpp"
#include "string_adjustment.hpp"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Testing the Note object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    std::cout << "Note: " << note->test_description() << std::endl;
    std::cout << "Name: " << note->test_description() << std::endl;
    CHECK(note->get_octave() == 2);
    CHECK(note->get_note() == NoteValue::C);
    CHECK(note->get_midi_note() == 36);
}

TEST_CASE("Testing the Chord object") {
    const auto intervals = {0, 4, 7};
    const auto chord = Chord::create_with_root_note(NoteValue::C, intervals);
    std::cout << "Chord: " << chord->test_description() << std::endl;
    CHECK(chord->test_description() == "CEG");
}

TEST_CASE("Testing the GuitarString object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    const auto guitarString = GuitarString::create_with_start_note(note, 13);
    std::cout << "GuitarString: " << guitarString->test_description() << std::endl;
    CHECK(guitarString->test_description() == "CC♯DD♯EFF♯GG♯AA♯BC");
    guitarString->adjust_string_by_steps(2);
    std::cout << "GuitarString: " << guitarString->test_description() << std::endl;
    CHECK(guitarString->test_description() == "DD♯EFF♯GG♯AA♯BCC♯D");
}

TEST_CASE("Testing the StringAdjustment object") {
    const auto adjustment = StringAdjustment::create_with_string_number(1, 1);
    std::cout << "StringAdjustment: " << adjustment->test_description() << std::endl;
    CHECK(adjustment->get_string_number() == 1);
    CHECK(adjustment->get_step() == 1);
}

TEST_CASE("Testing the GuitarAdjustment object") {
    const auto stringAdjustment = StringAdjustment::create_with_string_number(1, 1);
    const auto adjustments = std::vector<std::shared_ptr<StringAdjustment>>() = {stringAdjustment};
    const auto guitarAdjustment = GuitarAdjustment::create_with_string_adjustments(adjustments);
    std::cout << "guitarAdjustment: " << guitarAdjustment->test_description() << std::endl;
}

TEST_CASE("Testing harmonized scales") {
    const auto scale = HarmonizedScale::create_harmonized_scale_with_root_note(NoteValue::C, {2, 2, 1, 2, 2, 2});
    std::cout << scale->test_description() << std::endl;
}
