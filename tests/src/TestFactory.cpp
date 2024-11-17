//
// Created by John Sohn on 10/14/24.
//
#include <vector>
#include <doctest/doctest.h>
#include "chord.hpp"
#include "chord_DAO.hpp"
#include "chord_record.hpp"
#include "guitar.hpp"
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "note_value.hpp"
#include "scale.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"
#include "database_connection.hpp"
#include "guitar_factory.hpp"
#include "main.hpp"

TEST_CASE("Testing GuitarFactory") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);

    auto guitarRecord = GuitarRecord(std::nullopt, "test", 23, {}, 1, {}, {});
    auto guitarID = guitarDAO->add_guitar(guitarRecord);

    const auto guitars = guitarDAO->get_guitars();
    const auto guitar = GuitarFactory::create_guitar(guitars.front());
    CHECK(guitar->get_strings().size() > 0);
    CHECK(guitar->get_number_of_frets() > 0);
    CHECK(guitar->get_fret_markers().size() > 0);

    guitarDAO->delete_guitar(guitarID.value());
}

TEST_CASE("Testing ScaleFactory") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto scaleDAO = ScaleDAO::create_scale_dao(database);

    auto scaleRecord = ScaleRecord(std::nullopt, "test", {0, 1, 2});
    auto scaleID = scaleDAO->add_scale(scaleRecord);

    const auto scales = scaleDAO->get_scales();

    const auto scale = GuitarFactory::create_scale(NoteValue::C, scales.front());
    CHECK(scale->get_notes().size() > 0);

    scaleDAO->delete_scale(scaleID.value());
}

TEST_CASE("Testing ChordFactory") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto chordDAO = ChordDAO::create_chord_dao(database);

    auto chordRecord = ChordRecord(std::nullopt, "test", {0, 1, 2});
    auto chordID = chordDAO->add_chord(chordRecord);

    const auto chords = chordDAO->get_chords();
    const auto scale = GuitarFactory::create_chord(NoteValue::C, chords.front());
    CHECK(scale->get_notes().size() > 0);

    chordDAO->delete_chord(chordID.value());
}
