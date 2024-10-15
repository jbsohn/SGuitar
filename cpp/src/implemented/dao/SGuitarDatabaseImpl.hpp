//
// Created by john on 10/12/24.
//

#ifndef SGUITARDATABASEIMPL_H
#define SGUITARDATABASEIMPL_H

#include <SQLiteCpp/SQLiteCpp.h>
#include "SGuitar_database.hpp"

class SGuitarDatabaseImpl final : public SGuitarDatabase {
    SQLite::Database database;

public:
    explicit SGuitarDatabaseImpl(const std::string &path): database(path, SQLite::OPEN_READWRITE) {
    }

    SQLite::Database &getDatabase() { return database; }
};

#endif //SGUITARDATABASEIMPL_H
