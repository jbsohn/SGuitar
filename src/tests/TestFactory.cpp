//
// Created by John on 10/14/24.
//
#include <iostream>
#include <doctest/doctest.h>
#include "note_value.hpp"
#include "guitar_DAO.hpp"
#include "scale_DAO.hpp"
#include "chord_DAO.hpp"
#include "SGuitar_database.hpp"
#include "SGuitarFactory.hpp"

TEST_CASE("Testing GuitarFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../src/tests/test.sqlite3");
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    const auto guitars = guitarDAO->get_guitars();
    const auto guitarObject = SGuitarFactory::createGuitar(guitars[0]);
    CHECK(guitarObject->get_strings().size() > 0);
    std::cout << "guitar factory object: " << guitarObject->testDescription() << std::endl;
}

TEST_CASE("Testing ScaleFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../src/tests/test.sqlite3");
    const auto scaleDAO = ScaleDAO::create_scale_dao(database);
    const auto scales = scaleDAO->get_scales();
    const auto scaleObject = SGuitarFactory::createScale(NoteValue::C, scales[0]);
    CHECK(scaleObject->get_notes().size() > 0);
    std::cout << "scale factory object: " << scaleObject->testDescription() << std::endl;
}

TEST_CASE("Testing ChordFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../src/tests/test.sqlite3");
    const auto chordDAO = ChordDAO::create_chord_dao(database);
    const auto chords = chordDAO->get_chords();
    const auto scaleObject = SGuitarFactory::createChord(NoteValue::C, chords[0]);
    CHECK(scaleObject->get_notes().size() > 0);
    std::cout << "chord factory object: " << scaleObject->testDescription() << std::endl;
}
