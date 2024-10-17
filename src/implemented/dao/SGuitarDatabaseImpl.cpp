//
// Created by john on 10/12/24.
//

#include "SGuitarDatabaseImpl.hpp"

std::shared_ptr<SGuitarDatabase> SGuitarDatabase::create_sguitar_database(const std::string& path) {
    return std::make_shared<SGuitarDatabaseImpl>(path);
}
