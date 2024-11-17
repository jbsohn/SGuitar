//
// Created by John Sohn on 11/4/24.
//

#include <filesystem>
#include <doctest/doctest.h>
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "database_connection.hpp"
#include "guitar_import.hpp"
#include "main.hpp"

TEST_CASE("Testing full guitar import") {
    const auto database = DatabaseConnection::create_database_connection(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    GuitarImport::importJsonGuitarFromPath(Paths::lapSteelPath, guitarDAO);
    GuitarImport::importJsonGuitarFromPath(Paths::pedalSteelPath, guitarDAO);
    CHECK(guitarDAO->get_guitars()[1].number_of_frets == 26);
    CHECK(guitarDAO->get_guitars()[1].type == 2);
}