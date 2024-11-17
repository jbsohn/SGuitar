//
// Created by John Sohn on 10/12/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionImpl.hpp"
#include "ScaleDAOImpl.hpp"

std::vector<ScaleRecord> ScaleDAOImpl::get_scales() {
    std::vector<ScaleRecord> scales;

    SQLite::Statement query(db, "SELECT id, name, semitones FROM scale");
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        auto semitones_json = nlohmann::json::parse(query.getColumn(2).getString());
        std::vector<int32_t> semitones(semitones_json.begin(), semitones_json.end());
        scales.emplace_back(id, name, semitones);
    }

    return scales;
}

std::optional<int32_t> ScaleDAOImpl::add_scale(const ScaleRecord& scale) {
    const nlohmann::json json_semitones = std::vector(scale.semitones);

    SQLite::Statement query(db, "INSERT INTO scale (name, semitones) VALUES (?, ?) RETURNING id");
    query.bind(1, scale.name);
    query.bind(2, json_semitones.dump());
    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }

    return std::nullopt;
}

bool ScaleDAOImpl::update_scale(const ScaleRecord& scale) {
    const nlohmann::json json_semitones = std::vector(scale.semitones);

    SQLite::Statement query(db, "UPDATE scale SET name = ?, semitones = ? WHERE id=?");
    query.bind(1, scale.name);
    query.bind(2, json_semitones.dump());
    query.bind(3, scale.id.value());
    if (query.exec() != 1) {
        return false;
    }
    return true;
}

bool ScaleDAOImpl::delete_scale(const int32_t id) {
    SQLite::Statement query(db, "DELETE FROM scale WHERE id=?");
    query.bind(1, id);
    query.exec();
    return true;
}

std::shared_ptr<ScaleDAO> ScaleDAO::create_scale_dao(const std::shared_ptr<DatabaseConnection>& database) {
    auto* impl = dynamic_cast<DatabaseConnectionImpl*>(database.get());
    return std::make_shared<ScaleDAOImpl>(impl->getDatabase());
}
