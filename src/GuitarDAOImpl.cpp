//
// Created by John Sohn on 10/13/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include "SGuitarDatabaseImpl.hpp"
#include "GuitarDAOImpl.hpp"

std::vector<GuitarRecord> GuitarDAOImpl::get_guitars() {
    std::vector<GuitarRecord> guitars;

    SQLite::Statement query(db, "SELECT id, name, number_of_frets, fret_markers, type FROM guitar");
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto number_of_frets = query.getColumn(2).getInt();
        auto fret_markers_json = nlohmann::json::parse(query.getColumn(3).getString());
        std::vector<int32_t> fret_markers(fret_markers_json.begin(), fret_markers_json.end());
        const auto type = query.getColumn(4).getInt();
        const auto guitar_strings = get_guitar_strings(id);
        const auto guitar_adjustments = get_guitar_adjustments(id);
        guitars.emplace_back(id, name, number_of_frets, fret_markers, type, guitar_strings, guitar_adjustments);
    }

    return guitars;
}

void GuitarDAOImpl::add_guitar(const GuitarRecord& guitar) {
    std::string fret_markers;
    if (guitar.fret_markers.empty()) {
        fret_markers = "[3, 5, 7, 9, 12, 15, 17, 19, 21]";
    } else {
        const nlohmann::json json_fret_markers = std::vector(guitar.fret_markers);
        fret_markers = json_fret_markers.dump();
    }
    SQLite::Statement query(
        db, "INSERT INTO guitar(name, number_of_frets, fret_markers, type) VALUES (?,?,?,?) RETURNING id");
    query.bind(1, guitar.name);
    query.bind(2, guitar.number_of_frets);
    query.bind(3, fret_markers);
    query.bind(4, guitar.type);

    if (query.executeStep()) {
        const auto guitar_id = query.getColumn(0).getInt();
        for (const auto& guitar_string : guitar.guitar_strings) {
            auto guitar_string_update = guitar_string;
            guitar_string_update.guitar_id = guitar_id;
            if (auto guitar_string_id = add_guitar_string(guitar_string_update);
                guitar_string_id == SGuitarDatabase::SGUITAR_DB_UNSET) {
                return;
            }
        }

        for (const auto& guitar_adjustment : guitar.guitar_adjustments) {
            auto guitar_adjustment_update = guitar_adjustment;
            guitar_adjustment_update.guitar_id = guitar_id;
            auto guitar_adjustment_id = add_guitar_adjustment(guitar_adjustment_update);
            for (const auto& guitar_string_adjustment : guitar_adjustment.guitar_string_adjustments) {
                auto guitar_string_adjustment_update = guitar_string_adjustment;
                guitar_string_adjustment_update.guitar_adjustment_id = guitar_adjustment_id;
                add_guitar_string_adjustment(guitar_string_adjustment_update);
            }
        }
    }
}

int32_t GuitarDAOImpl::update_guitar(const GuitarRecord& guitar) {
    return SGuitarDatabase::SGUITAR_DB_UNSET;
}

void GuitarDAOImpl::delete_guitar(int32_t id) {}

std::vector<GuitarStringRecord> GuitarDAOImpl::get_guitar_strings(int guitar_id) {
    std::vector<GuitarStringRecord> strings;

    SQLite::Statement query(db, "SELECT id, string_number, start_note, octave FROM guitar_string WHERE guitar_id=?");
    query.bind(1, guitar_id);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto string_number = query.getColumn(1).getInt();
        const auto start_note = query.getColumn(2).getString();
        const auto octave = query.getColumn(3).getInt();
        strings.emplace_back(id, guitar_id, string_number, start_note, octave);
    }

    return strings;
}

int32_t GuitarDAOImpl::add_guitar_string(const GuitarStringRecord& guitar_string_record) {
    SQLite::Statement query(
        db, "INSERT INTO guitar_string(guitar_id, string_number, start_note, octave) VALUES (?,?,?,?) RETURNING id");
    query.bind(1, guitar_string_record.guitar_id);
    query.bind(2, guitar_string_record.string_number);
    query.bind(3, guitar_string_record.start_note);
    query.bind(4, guitar_string_record.octave);
    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }
    return SGuitarDatabase::SGUITAR_DB_UNSET;
}

std::vector<GuitarAdjustmentRecord> GuitarDAOImpl::get_guitar_adjustments(int guitar_id) {
    std::vector<GuitarAdjustmentRecord> adjustments;

    SQLite::Statement query(db, "SELECT id, name FROM guitar_adjustment WHERE guitar_id=?");
    query.bind(1, guitar_id);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto string_adjustments = get_guitar_string_adjustments(id);
        adjustments.emplace_back(id, guitar_id, name, string_adjustments);
    }

    return adjustments;
}

int32_t GuitarDAOImpl::add_guitar_adjustment(const GuitarAdjustmentRecord& guitar_adjustment_record) {
    SQLite::Statement query(db, "INSERT INTO guitar_adjustment(guitar_id, name) VALUES (?,?) RETURNING id");
    query.bind(1, guitar_adjustment_record.guitar_id);
    query.bind(2, guitar_adjustment_record.name);
    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }
    return SGuitarDatabase::SGUITAR_DB_UNSET;
}

std::vector<GuitarStringAdjustmentRecord> GuitarDAOImpl::get_guitar_string_adjustments(const int guitar_adjustment_id) {
    std::vector<GuitarStringAdjustmentRecord> string_adjustments;

    SQLite::Statement query(
        db, "SELECT id, string_number, step FROM guitar_string_adjustment WHERE guitar_adjustment_id=?");
    query.bind(1, guitar_adjustment_id);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto string_number = query.getColumn(1).getInt();
        const auto step = query.getColumn(2).getInt();
        string_adjustments.emplace_back(id, guitar_adjustment_id, string_number, step);
    }

    return string_adjustments;
}

int32_t GuitarDAOImpl::add_guitar_string_adjustment(
    const GuitarStringAdjustmentRecord& guitar_string_adjustment_record) {
    SQLite::Statement query(
        db,
        "INSERT INTO guitar_string_adjustment(guitar_adjustment_id, string_number, step) VALUES (?,?,?) RETURNING id");
    query.bind(1, guitar_string_adjustment_record.guitar_adjustment_id);
    query.bind(2, guitar_string_adjustment_record.string_number);
    query.bind(3, guitar_string_adjustment_record.step);

    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }
    return SGuitarDatabase::SGUITAR_DB_UNSET;
}

std::shared_ptr<GuitarDAO> GuitarDAO::create_guitar_dao(const std::shared_ptr<SGuitarDatabase>& database) {
    auto* impl = dynamic_cast<SGuitarDatabaseImpl*>(database.get());
    return std::make_shared<GuitarDAOImpl>(impl->getDatabase());
}
