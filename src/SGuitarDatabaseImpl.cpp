//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "SGDatabaseConnectionImpl.hpp"

std::shared_ptr<SGDatabaseConnection> SGDatabaseConnection::create_sgdatabase_connection(const std::string& path) {
    return std::make_shared<SGDatabaseConnectionImpl>(path);
}
