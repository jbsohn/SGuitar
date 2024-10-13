//
// Created by john on 10/12/24.
//

#include <nlohmann/json.hpp>
#include "ScaleDAOImpl.hpp"
#include "SGuitarDAOImpl.hpp"

std::vector<ScaleRecord> ScaleDAOImpl::get_scales() {
    std::vector<ScaleRecord> scales;

    SQLite::Statement query(
        db,
        "SELECT id, name, semitones FROM scale");
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        auto intervals_json  = nlohmann::json::parse(query.getColumn(2).getString());
        std::vector<int32_t> intervals(intervals_json.begin(), intervals_json.end());
        scales.emplace_back(id, name, intervals);
    }

    return scales;
}

int32_t ScaleDAOImpl::add_scale(const ScaleRecord &scale) {
    int32_t id = -1;

    SQLite::Statement query(
        db,
        "INSERT INTO scale (name, semitones) VALUES (?, ?) RETURNING id");

    const nlohmann::json json_intervals = std::vector(scale.intervals);
    query.bind(1, scale.name);
    query.bind(2, json_intervals.dump());
    if (query.executeStep()) {
        id = query.getColumn(0).getInt();
    }

    return id;
}

void ScaleDAOImpl::update_scale(const ScaleRecord &scale) {
    const nlohmann::json json_intervals = std::vector(scale.intervals);

    SQLite::Statement query(
        db,
        "UPDATE scale SET name = ?, semitones = ? WHERE id=?");
    query.bind(1, scale.name);
    query.bind(2, json_intervals.dump());
    query.bind(3, scale.id);
    query.exec();
}

void ScaleDAOImpl::delete_scale(const int32_t id) {
    SQLite::Statement query(
        db,
        "DELETE FROM scale WHERE id=?");
    query.bind(1, id);
    query.exec();
}

std::shared_ptr<ScaleDAO> ScaleDAO::create_scale_dao(const std::shared_ptr<SguitarDAO> &database) {
    auto *impl = dynamic_cast<SGuitarDAOImpl *>(database.get());
    return std::make_shared<ScaleDAOImpl>(impl->getDatabase());
}
