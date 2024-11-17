//
// Created by John Sohn on 10/5/24.
//

#include <doctest/doctest.h>
#include <chord.hpp>
#include "note_value.hpp"

TEST_CASE("Testing Chord: Major") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7});
    CHECK(chord->test_description() == "CEG");
}

TEST_CASE("Testing Chord: Minor") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7});
    CHECK(chord->test_description() == "CE♭G");
}

TEST_CASE("Testing Chord: Augmented") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 8});
    CHECK(chord->test_description() == "CEA♭");
}

TEST_CASE("Testing Chord: Diminished") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 6});
    CHECK(chord->test_description() == "CE♭G♭");
}

TEST_CASE("Testing Chord: Suspended Fourth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 5, 7});
    CHECK(chord->test_description() == "CFG");
}

TEST_CASE("Testing Chord: Suspended Second") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {{0, 2, 7}});
    CHECK(chord->test_description() == "CDG");
}

TEST_CASE("Testing Chord: Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 10});
    CHECK(chord->test_description() == "CEGB♭");
}

TEST_CASE("Testing Chord: Major Sixth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 9});
    CHECK(chord->test_description() == "CEGA");
}

TEST_CASE("Testing Chord: Minor Sixth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7, 9});
    CHECK(chord->test_description() == "CE♭GA");
}

TEST_CASE("Testing Chord: Major Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 11});
    CHECK(chord->test_description() == "CEGB");
}

TEST_CASE("Testing Chord: Minor Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7, 10});
    CHECK(chord->test_description() == "CE♭GB♭");
}

TEST_CASE("Testing Chord: Ninth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 10, 2});
    CHECK(chord->test_description() == "CEGB♭D");
}
