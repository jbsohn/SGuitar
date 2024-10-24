
#include <iostream>
#include <doctest/doctest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <fmt/format.h>
#include "SGuitar_database.hpp"
#include "scale_record.hpp"
#include "scale_DAO.hpp"
#include "chord_record.hpp"
#include "chord_DAO.hpp"
#include "guitar_record.hpp"
#include "guitar_DAO.hpp"

TEST_CASE("Testing DB: SELECT") {
    const SQLite::Database db("./db/test.sqlite3");
    std::cout << "SELECT Scales..." << std::endl;
    SQLite::Statement queryScale(db, "SELECT * FROM scale");
    while (queryScale.executeStep()) {
        std::cout << fmt::format("{}: {}, {}\n",
                                 queryScale.getColumn(0).getInt(),
                                 queryScale.getColumn(1).getString(),
                                 queryScale.getColumn(2).getString());
    }

    std::cout << "SELECT Chords...";
    SQLite::Statement queryChord(db, "SELECT * FROM chord");
    while (queryChord.executeStep()) {
        std::cout << fmt::format("{}: {}, {}\n",
                                 queryChord.getColumn(0).getInt(),
                                 queryChord.getColumn(1).getString(),
                                 queryChord.getColumn(2).getString());
    }
}

TEST_CASE("Testing ScaleDAO get") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto scale = ScaleDAO::create_scale_dao(database);
    auto scales = scale->get_scales();
    CHECK(scales.size() > 0);
}

TEST_CASE("Testing ScaleDAO add/delete") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto scale = ScaleDAO::create_scale_dao(database);
    std::vector semitones = {0, 1, 2};
    auto id = scale->add_scale(ScaleRecord(0, "test", semitones));
    CHECK(id > 0);
    scale->delete_scale(id);
}

TEST_CASE("Testing ChordDAO add/delete") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto chord = ChordDAO::create_chord_dao(database);
    std::vector intervals = {0, 1, 2};
    auto id = chord->add_chord(ChordRecord(0, "test", intervals));
    CHECK(id > 0);
    chord->delete_chord(id);
}

TEST_CASE("Testing GuitarDAO get/add/delete") {
    const auto database = SGuitarDatabase::create_sguitar_database("../tests/db/test.sqlite3");
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    auto guitars = guitarDAO->get_guitars();
    CHECK(guitars.size() > 0);
}
