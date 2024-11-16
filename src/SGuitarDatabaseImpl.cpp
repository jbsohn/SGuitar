//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "SGuitarDatabaseImpl.hpp"

std::shared_ptr<SGDatabaseConnection> SGDatabaseConnection::create_SGDatabase_connection(const std::string& path) {
    return std::make_shared<SGDatabaseConnectionImpl>(path);
}
