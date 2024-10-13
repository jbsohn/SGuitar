//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "ScaleDAOImpl.hpp"
#include "SGuitarDBImpl.hpp"

std::vector<ScaleRecord> ScaleDAOImpl::get_scales() {
    SQLite::Statement queryScale(
        db,
        "SELECT id, name, semitones FROM scale");
    return {};
}

void ScaleDAOImpl::add_scale(const ScaleRecord &scale) {
}

void ScaleDAOImpl::update_scale(int32_t id, const ScaleRecord &scale) {
}

void ScaleDAOImpl::delete_scale(int32_t id) {
}

std::shared_ptr<ScaleDAO> ScaleDAO::create_scale_db(const std::shared_ptr<SguitarDB> &database) {
    auto *impl = dynamic_cast<SGuitarDBImpl *>(database.get());
    return std::make_shared<ScaleDAOImpl>(impl->getDatabase());
}
