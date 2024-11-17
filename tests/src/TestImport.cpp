//
// Created by John Sohn on 11/4/24.
//

#include <filesystem>
#include <doctest/doctest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include "DatabaseConnectionImpl.hpp"
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
    CHECK(guitarDAO->get_guitars().front().number_of_frets == 26);
    CHECK(guitarDAO->get_guitars().front().type == 2);

    auto* impl = dynamic_cast<DatabaseConnectionImpl*>(database.get());
    auto db = std::move(impl->getDatabase());
    db.exec("delete from guitar");
    db.exec("delete from guitar_string");
    db.exec("delete from guitar_adjustment");
    db.exec("delete from guitar_string_adjustment");
    db.exec("delete from scale");
    db.exec("delete from chord");
}
