//
// Created by John Sohn on 11/15/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <doctest/doctest.h>
#include <fmt/format.h>
#include <iostream>
#include "SGDatabase_connection.hpp"
#include "chord_DAO.hpp"
#include "chord_record.hpp"
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"
#include "main.hpp"

TEST_CASE("Testing ScaleDAO get") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto scale = ScaleDAO::create_scale_dao(database);
    auto scales = scale->get_scales();
    CHECK(scales.size() > 0);
}

TEST_CASE("Testing ScaleDAO add/update/delete") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto scale = ScaleDAO::create_scale_dao(database);
    std::vector semitones = {0, 1, 2};

    auto scaleRecord = ScaleRecord(std::nullopt, "test", semitones);
    auto id = scale->add_scale(scaleRecord);
    CHECK(id.value() > 0);

    scaleRecord.id = id.value();
    scaleRecord.name = "test2";
    CHECK(scale->update_scale(scaleRecord));

    if (id.value() > 0) {
        CHECK(scale->delete_scale(id.value()));
    }
}

TEST_CASE("Testing ChordDAO get") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto chord = ChordDAO::create_chord_dao(database);
    auto chords = chord->get_chords();
    CHECK(chords.size() > 0);
}

TEST_CASE("Testing ChordDAO add/update/delete") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto chord = ChordDAO::create_chord_dao(database);
    std::vector intervals = {0, 1, 2};

    auto chordRecord = ChordRecord(std::nullopt, "test", intervals);
    auto id = chord->add_chord(chordRecord);
    CHECK(id.value() > 0);

    chordRecord.id = id.value();
    chordRecord.name = "test2";
    CHECK(chord->update_chord(chordRecord));

    if (id.value() > 0) {
        CHECK(chord->delete_chord(id.value()));
    }
}

TEST_CASE("Testing GuitarDAO get") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    auto guitars = guitarDAO->get_guitars();
    CHECK(guitars.size() > 0);
}

TEST_CASE("Testing ChordDAO add/update/delete") {
    const auto database = SGDatabaseConnection::create_SGDatabase_connection(Paths::dbPath);
    const auto guitar = GuitarDAO::create_guitar_dao(database);

    auto guitarRecord = GuitarRecord(std::nullopt, "test", 23, {}, 1, {}, {});
    auto id = guitar->add_guitar(guitarRecord);
    CHECK(id.value() > 0);

    guitarRecord.id = id.value();
    guitarRecord.name = "test2";
    CHECK(guitar->update_guitar(guitarRecord));

    if (id.value() > 0) {
        CHECK(guitar->delete_guitar(id.value()));
    }
}
