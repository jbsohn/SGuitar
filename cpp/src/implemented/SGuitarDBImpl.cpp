//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "sguitar_DB.hpp"
#include "SGuitarDBImpl.h"

std::shared_ptr<SguitarDB> SguitarDB::create_sguitar_database(const std::string& path) {
    return std::make_shared<SGuitarDBImpl>(path);
}
