//
// Created by john on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include "sguitar_DB.hpp"
#include "scale_DAO.hpp"
#include "scale_record.hpp"
#include "SGuitarDBImpl.h"

class ScaleDAOImpl final : public ScaleDAO {
    const SQLite::Database& db;
public:
    explicit ScaleDAOImpl(const SQLite::Database& database) : db(database) {
    }

    std::vector<ScaleRecord> get_scales() override {
        SQLite::Statement queryScale(
            db,
            "SELECT id, name, semitones FROM scale");
        return {};
    }

    void add_scale(const ScaleRecord & scale) override {

    }

    void update_scale(int32_t id, const ScaleRecord & scale) override {

    }

    void delete_scale(int32_t id) override {

    }
};

std::shared_ptr<ScaleDAO> ScaleDAO::create_scale_db(const std::shared_ptr<SguitarDB> & database) {
    auto *impl = dynamic_cast<SGuitarDBImpl*>(database.get());
    return std::make_shared<ScaleDAOImpl>(impl->getDatabase());
}
