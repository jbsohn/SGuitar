//
// Created by John Sohn on 10/12/24.
//

#ifndef SG_DATABASE_CONNECTION_IMPL_H
#define SG_DATABASE_CONNECTION_IMPL_H

#include "database_connection.hpp"

class DatabaseConnectionImpl final : public DatabaseConnection {
    SQLite::Database database;

public:
    explicit DatabaseConnectionImpl(const std::string& path) : database(path, SQLite::OPEN_READWRITE) {}

    SQLite::Database& getDatabase() { return database; }
};

#endif  // SG_DATABASE_CONNECTION_IMPL_H
