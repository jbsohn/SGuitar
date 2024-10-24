//
// Created by John on 10/14/24.
//
#include <iostream>
#include <vector>
#include <doctest/doctest.h>

#include <chord.hpp>
#include <guitar.hpp>
#include <scale.hpp>

#include "SGuitar_database.hpp"
#include "SGuitar_factory.hpp"
#include "chord_DAO.hpp"
#include "chord_record.hpp"
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "note_value.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"

TEST_CASE("Testing GuitarFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    const auto guitars = guitarDAO->get_guitars();
    const auto guitar = SGuitarFactory::create_guitar(guitars[0]);
    CHECK(guitar->get_strings().size() > 0);
    std::cout << "guitar factory object: " << std::endl << guitar->test_description() << std::endl;
}

TEST_CASE("Testing ScaleFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto scaleDAO = ScaleDAO::create_scale_dao(database);
    const auto scales = scaleDAO->get_scales();
    const auto scale = SGuitarFactory::create_scale(NoteValue::C, scales[0]);
    CHECK(scale->get_notes().size() > 0);
    std::cout << "scale factory object: " << scale->test_description() << std::endl;
}

TEST_CASE("Testing ChordFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto chordDAO = ChordDAO::create_chord_dao(database);
    const auto chords = chordDAO->get_chords();
    const auto scale = SGuitarFactory::create_chord(NoteValue::C, chords[0]);
    CHECK(scale->get_notes().size() > 0);
    std::cout << "chord factory object: " << scale->test_description() << std::endl;
}
