//
// Created by john on 10/12/24.
//

#ifndef SGUITAR_DATABASE_IMPL_H
#define SGUITAR_DATABASE_IMPL_H

#include "SGuitar_database.hpp"

class SGuitarDatabaseImpl final : public SGuitarDatabase {
    SQLite::Database database;

public:
    explicit SGuitarDatabaseImpl(const std::string& path) : database(
        path,
        SQLite::OPEN_READWRITE
    ) {
    }

    SQLite::Database& getDatabase() { return database; }
};

#endif  // SGUITAR_DATABASE_IMPL_H
