//
// Created by John Sohn on 11/15/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <doctest/doctest.h>
#include <fmt/format.h>
#include <iostream>
#include "database_connection.hpp"
#include "chord_DAO.hpp"
#include "chord_record.hpp"
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"
#include "main.hpp"

TEST_SUITE("Testing ScaleDAO") {
std::optional<int> scaleID;

TEST_CASE("Testing ScaleDAO add/update") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto scale = ScaleDAO::create_scale_dao(database);
    auto scaleRecord = ScaleRecord(std::nullopt, "test", {0, 1, 2});
    scaleID = scale->add_scale(scaleRecord);
    CHECK(scaleID.value() > 0);

    scaleRecord.id = scaleID.value();
    scaleRecord.name = "test2";
    CHECK(scale->update_scale(scaleRecord));
}

TEST_CASE("Testing ScaleDAO get") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto scale = ScaleDAO::create_scale_dao(database);
    auto scales = scale->get_scales();
    CHECK(scales.size() > 0);
}

TEST_CASE("Testing ScaleDAO delete") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto scale = ScaleDAO::create_scale_dao(database);
    if (scaleID.value() > 0) {
        CHECK(scale->delete_scale(scaleID.value()));
    }
}
}

TEST_SUITE("Testing ChordDAO") {
std::optional<int> chordID;

TEST_CASE("Testing ChordDAO add/update") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto chord = ChordDAO::create_chord_dao(database);
    auto chordRecord = ChordRecord(std::nullopt, "test", {0, 1, 2});
    chordID = chord->add_chord(chordRecord);
    CHECK(chordID.value() > 0);

    chordRecord.id = chordID.value();
    chordRecord.name = "test2";
    CHECK(chord->update_chord(chordRecord));
}

TEST_CASE("Testing ChordDAO get") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto chord = ChordDAO::create_chord_dao(database);
    auto chords = chord->get_chords();
    CHECK(chords.size() > 0);
}

TEST_CASE("Testing ChordDAO delete") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto chord = ChordDAO::create_chord_dao(database);
    if (chordID.value() > 0) {
        CHECK(chord->delete_chord(chordID.value()));
    }
}
}

TEST_SUITE("Testing GuitarDAO") {
std::optional<int> guitarID;

TEST_CASE("Testing GuitarDAO add/update") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    auto guitarRecord = GuitarRecord(std::nullopt, "test", 23, {}, 1, {}, {});
    guitarID = guitarDAO->add_guitar(guitarRecord);
    CHECK(guitarID.value() > 0);

    guitarRecord.id = guitarID.value();
    guitarRecord.name = "test2";
    CHECK(guitarDAO->update_guitar(guitarRecord));
}

TEST_CASE("Testing GuitarDAO get") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    auto guitars = guitarDAO->get_guitars();
    CHECK(guitars.size() > 0);
}

TEST_CASE("Testing GuitarDAO delete") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    if (guitarID.value() > 0) {
        CHECK(guitarDAO->delete_guitar(guitarID.value()));
    }
}
}
