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
#include "SGuitar_database.hpp"
#include "SGuitar_factory.hpp"
#include "main.hpp"

TEST_CASE("Testing GuitarFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    const auto guitars = guitarDAO->get_guitars();
    const auto guitar = SGuitarFactory::create_guitar(guitars[0]);
    CHECK(guitar->get_strings().size() > 0);
    CHECK(guitar->get_number_of_frets() > 0);
    CHECK(guitar->get_fret_markers().size() > 0);
}

TEST_CASE("Testing ScaleFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database(Paths::dbPath);
    const auto scaleDAO = ScaleDAO::create_scale_dao(database);
    const auto scales = scaleDAO->get_scales();
    const auto scale = SGuitarFactory::create_scale(NoteValue::C, scales[0]);
    CHECK(scale->get_notes().size() > 0);
}

TEST_CASE("Testing ChordFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database(Paths::dbPath);
    const auto chordDAO = ChordDAO::create_chord_dao(database);
    const auto chords = chordDAO->get_chords();
    const auto scale = SGuitarFactory::create_chord(NoteValue::C, chords[0]);
    CHECK(scale->get_notes().size() > 0);
}
