//
//  SGuitarTest
//
//  Created by John Sohn on 8/18/24.
//
#include <vector>
#include <doctest/doctest.h>
#include "chord.hpp"
#include "guitar.hpp"
#include "guitar_adjustment.hpp"
#include "guitar_string.hpp"
#include "harmonized_scale.hpp"
#include "note.hpp"
#include "note_value.hpp"
#include "string_adjustment.hpp"

TEST_CASE("Testing the GuitarString object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    const auto guitarString = GuitarString::create_with_start_note(note, 13);
    CHECK(guitarString->test_description() == "CC♯DD♯EFF♯GG♯AA♯BC");
    guitarString->adjust_string_by_steps(2);
    CHECK(guitarString->test_description() == "DD♯EFF♯GG♯AA♯BCC♯D");
}

TEST_CASE("Testing the StringAdjustment object") {
    const auto adjustment = StringAdjustment::create_with_string_number(1, 1);
    CHECK(adjustment->get_string_number() == 1);
    CHECK(adjustment->get_step() == 1);
}

TEST_CASE("Testing the GuitarAdjustment object") {
    const auto stringAdjustment = StringAdjustment::create_with_string_number(1, 1);
    const auto adjustments = std::vector<std::shared_ptr<StringAdjustment>>() = {stringAdjustment};
    const auto guitarAdjustment = GuitarAdjustment::create_with_string_adjustments(adjustments);
    CHECK(guitarAdjustment->get_string_adjustments().front()->get_string_number() == 1);
    CHECK(guitarAdjustment->get_string_adjustments().front()->get_step() == 1);
}

TEST_CASE("Testing harmonized scales") {
    const auto scale = HarmonizedScale::create_harmonized_scale_with_root_note(NoteValue::C, {2, 2, 1, 2, 2, 2});
    CHECK(scale->get_chords()[0]->test_description() == "CDEFGAB");
    CHECK(scale->get_chords()[1]->test_description() == "EFGABCD");
    CHECK(scale->get_chords()[2]->test_description() == "GABCDEF");
}
