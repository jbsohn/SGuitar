//
// Created by John Sohn on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "DatabaseConnectionImpl.hpp"

std::shared_ptr<DatabaseConnection> DatabaseConnection::create_database_connection(const std::string& path) {
    return std::make_shared<DatabaseConnectionImpl>(path);
}
