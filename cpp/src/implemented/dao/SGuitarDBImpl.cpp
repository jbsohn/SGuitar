//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "SGuitarDBImpl.hpp"

std::shared_ptr<SguitarDB> SguitarDB::create_sguitar_database(const std::string &path) {
    return std::make_shared<SGuitarDBImpl>(path);
}
