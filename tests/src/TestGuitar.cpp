//
// Created by John Sohn on 11/24/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <doctest/doctest.h>
#include <fmt/format.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "database_connection.hpp"
#include "chord_DAO.hpp"
#include "chord_record.hpp"
#include "guitar_string.hpp"
#include "guitar.hpp"
#include "guitar_adjustment.hpp"
#include "note.hpp"
#include "note_value.hpp"
#include "string_adjustment.hpp"

TEST_CASE("") {
    int number_of_frets = 12;
    const std::vector guitar_strings = {GuitarString::create(),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::F_SHARP, 4), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::D_SHARP, 4), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::G_SHARP, 4), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::E, 4), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::B, 3), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::G_SHARP, 3), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::F_SHARP, 3), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::E, 3), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::D, 3), number_of_frets
                                            ),
                                        GuitarString::create_with_start_note(
                                            Note::create_with_note(NoteValue::B, 2), number_of_frets
                                            )};
    const auto string_adjustments = {StringAdjustment::create_with_string_number(4, +1),
                                     StringAdjustment::create_with_string_number(8, +1)};
    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>> guitar_adjustments = {};
    guitar_adjustments["LKL"] = GuitarAdjustment::create_with_string_adjustments(string_adjustments, 0, 0);

    auto guitar = Guitar::create(number_of_frets, {}, guitar_strings, guitar_adjustments);
    auto strings = guitar->get_strings();
    CHECK(guitar->is_adjustment_activated("LKL") == false);
    CHECK(strings[4]->get_notes()[0]->get_note() == NoteValue::E);
    CHECK(strings[8]->get_notes()[0]->get_note() == NoteValue::E);

    guitar->set_adjustment_activated("LKL", true);
    CHECK(guitar->is_adjustment_activated("LKL") == true);
    strings = guitar->get_strings();
    CHECK(strings[4]->get_notes()[0]->get_note() == NoteValue::F);
    CHECK(strings[8]->get_notes()[0]->get_note() == NoteValue::F);

    guitar->set_adjustment_activated("LKL", false);
    strings = guitar->get_strings();
    CHECK(strings[4]->get_notes()[0]->get_note() == NoteValue::E);
    CHECK(strings[8]->get_notes()[0]->get_note() == NoteValue::E);
}
