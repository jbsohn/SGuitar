//
// Created by john on 10/5/24.
//

#include <iostream>
#include <doctest/doctest.h>
#include "note_value.hpp"
#include "scale.hpp"

TEST_CASE("Testing Scale: C Major") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {2, 2, 1, 2, 2, 2});
    std::cout << "C Major: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CDEFGAB");
}

TEST_CASE("Testing Scale: C Natural Minor") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {2, 1, 2, 2, 1, 2});
    std::cout << "C Natural Minor: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CDE♭FGA♭B♭");
}

TEST_CASE("Testing Scale: C Harmonic Minor") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {2, 1, 2, 2, 1, 3});
    std::cout << "C Harmonic Minor: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CDE♭FGA♭B");
}

TEST_CASE("Testing Scale: C Pentatonic Minor") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {3, 2, 2, 3});
    std::cout << "C Pentatonic Minor: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CE♭FGB♭");
}

TEST_CASE("Testing Scale: C Pentatonic Major") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {2, 2, 3, 2});
    std::cout << "C Pentatonic Major: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CDEGA");
}

TEST_CASE("Testing Scale: C Minor Blues") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {3, 2, 1, 1, 3});
    std::cout << "C Minor Blues: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CE♭FG♭GB♭");
}

TEST_CASE("Testing Scale: C Major Blues") {
    const auto scale = Scale::create_with_root_note(NoteValue::C, {2, 1, 1, 3, 2});
    std::cout << "C Major Blues: " << scale->test_description() << std::endl;
    CHECK(scale->test_description() == "CDE♭EGA");
}
