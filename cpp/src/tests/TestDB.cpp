
#include <format>
#include <iostream>
#include <doctest/doctest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "sguitar_DAO.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"

TEST_CASE("Testing DB: SELECT") {
    const SQLite::Database db("../../db/main.sqlite3");

    std::cout << "SELECT Scales..." << std::endl;
    SQLite::Statement queryScale(db, "SELECT * FROM scale");
    while (queryScale.executeStep()) {
        std::cout << std::format("{}: {}, {}\n",
            queryScale.getColumn(0).getInt(),
            queryScale.getColumn(1).getString(),
            queryScale.getColumn(2).getString());
    }

    std::cout << "SELECT Chords...";
    SQLite::Statement queryChord(db, "SELECT * FROM chord");
    while (queryChord.executeStep()) {
        std::cout << std::format("{}: {}, {}\n",
            queryChord.getColumn(0).getInt(),
            queryChord.getColumn(1).getString(),
            queryChord.getColumn(2).getString());
    }
}

TEST_CASE("Testing ScaleDAO get") {
    const auto database = SguitarDAO::create_sguitar_dao("../../db/main.sqlite3");
    const auto scale = ScaleDAO::create_scale_dao(database);
    auto scales = scale->get_scales();
    CHECK(scales.size() > 0);
}

TEST_CASE("Testing ScaleDAO add/delete") {
    const auto database = SguitarDAO::create_sguitar_dao("../../db/main.sqlite3");
    const auto scale = ScaleDAO::create_scale_dao(database);
    std::vector semitones = { 0, 1, 2};
    auto id = scale->add_scale(ScaleRecord(0, "test", semitones));
    CHECK(id > 0);
    scale->delete_scale(id);
}
