//
// Created by John Sohn on 11/4/24.
//

#include <filesystem>
#include <doctest/doctest.h>
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "SGuitar_database.hpp"
#include "SGuitar_import.hpp"
#include "main.hpp"

TEST_CASE("Testing full guitar import") {
    const auto database = SGuitarDatabase::create_sguitar_database(Paths::dbPath);
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    SGuitarImport::importJsonGuitarFromPath("../import/Lap Steel", guitarDAO);
    SGuitarImport::importJsonGuitarFromPath("../import/Pedal Steel", guitarDAO);
    CHECK(guitarDAO->get_guitars()[1].number_of_frets == 26);
    CHECK(guitarDAO->get_guitars()[1].type == 2);
}