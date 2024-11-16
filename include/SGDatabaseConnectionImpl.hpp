//
// Created by john on 10/12/24.
//

#ifndef SG_DATABASE_CONNECTION_IMPL_H
#define SG_DATABASE_CONNECTION_IMPL_H

#include "SGDatabase_connection.hpp"

class SGDatabaseConnectionImpl final : public SGDatabaseConnection {
    SQLite::Database database;

public:
    explicit SGDatabaseConnectionImpl(const std::string& path) : database(
        path,
        SQLite::OPEN_READWRITE
    ) {
    }

    SQLite::Database& getDatabase() { return database; }
};

#endif  // SG_DATABASE_CONNECTION_IMPL_H
