//
// Created by John on 10/14/24.
//
#include <guitar_DAO.hpp>
#include <SGuitar_database.hpp>
#include <doctest/doctest.h>
#include "SGuitarFactory.hpp"

TEST_CASE("Testing GuitarFactory") {
    const auto database = SGuitarDatabase::create_sguitar_database("../src/tests/test.sqlite3");
    const auto guitarDAO = GuitarDAO::create_guitar_dao(database);
    const auto guitars = guitarDAO->get_guitars();
    auto guitarObject = SGuitarFactory::createGuitar(guitars[0]);
    CHECK(guitarObject->get_strings().size() > 0);
}
