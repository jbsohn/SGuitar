//
// Created by john on 10/5/24.
//

#include <iostream>
#include <chord.hpp>
#include <note_value.hpp>
#include <doctest/doctest.h>

TEST_CASE("Testing Chord: Major") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7});
    std::cout << "Major: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEG");
}

TEST_CASE("Testing Chord: Minor") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7});
    std::cout << "Minor: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CE♭G");
}

TEST_CASE("Testing Chord: Augmented") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 8});
    std::cout << "Augmented: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEA♭");
}

TEST_CASE("Testing Chord: Diminished") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 6});
    std::cout << "Diminished: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CE♭G♭");
}

TEST_CASE("Testing Chord: Suspended Fourth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 5, 7});
    std::cout << "Suspended Fourth: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CFG");
}

TEST_CASE("Testing Chord: Suspended Second") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {{0, 2, 7}});
    std::cout << "Suspended Second: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CDG");
}

TEST_CASE("Testing Chord: Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 10});
    std::cout << "Seventh: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEGB♭");
}

TEST_CASE("Testing Chord: Major Sixth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 9});
    std::cout << "Major Sixth: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEGA");
}

TEST_CASE("Testing Chord: Minor Sixth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7, 9});
    std::cout << "Minor Sixth: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CE♭GA");
}

TEST_CASE("Testing Chord: Major Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 11});
    std::cout << "Major Seventh: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEGB");
}

TEST_CASE("Testing Chord: Minor Seventh") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 3, 7, 10});
    std::cout << "Minor Seventh: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CE♭GB♭");
}

TEST_CASE("Testing Chord: Ninth") {
    const auto chord = Chord::create_with_root_note(NoteValue::C, {0, 4, 7, 10, 2});
    std::cout << "Ninth: " << chord->testDescription() << std::endl;
    CHECK(chord->testDescription() == "CEGB♭D");
}
