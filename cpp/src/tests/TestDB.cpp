
#include <format>
#include <iostream>
#include <doctest/doctest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "sguitar_DB.hpp"
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

TEST_CASE("Testing ScaleDAO") {
    const auto database = SguitarDB::create_sguitar_database("../../db/main.sqlite3");
    const auto scale = ScaleDAO::create_scale_db(database);
    scale->get_scales();
}

