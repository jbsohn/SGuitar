//
// Created by John Sohn on 10/13/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include "DatabaseConnectionImpl.hpp"
#include "GuitarDAOImpl.hpp"

std::vector<GuitarRecord> GuitarDAOImpl::get_guitars() {
    std::vector<GuitarRecord> guitars;

    const std::string sql = "SELECT id, name, number_of_frets, fret_markers, type FROM guitar";
    SQLite::Statement query(db, sql);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto number_of_frets = query.getColumn(2).getInt();
        const auto fret_markers_string = query.getColumn(3).getString();
        const auto type = query.getColumn(4).getInt();
        const auto guitar_strings = get_guitar_strings(id);
        const auto guitar_adjustments = get_guitar_adjustments(id);
        auto fret_markers = getFretMarkersFromJson(fret_markers_string);
        guitars.emplace_back(id, name, number_of_frets, fret_markers, type, guitar_strings, guitar_adjustments);
    }

    return guitars;
}

std::optional<int32_t> GuitarDAOImpl::add_guitar(const GuitarRecord& guitar) {
    const std::string fret_markers = fretMarkersAsJson(guitar.fret_markers);
    const std::string sql = "INSERT INTO guitar(name, number_of_frets, fret_markers, type) VALUES (?,?,?,?)";
    SQLite::Transaction transaction(db);

    int32_t guitar_id;
    {
        SQLite::Statement query(db, sql);
        query.bind(1, guitar.name);
        query.bind(2, guitar.number_of_frets);
        query.bind(3, fret_markers);
        query.bind(4, guitar.type);

        if (query.exec() != 1) {
            return std::nullopt;
        }

        guitar_id = static_cast<int32_t>(db.getLastInsertRowid());
    }

    for (const auto& guitar_string : guitar.guitar_strings) {
        auto guitar_string_update = guitar_string;
        guitar_string_update.guitar_id = guitar_id;
        if (!add_guitar_string(guitar_string_update).has_value()) {
            return std::nullopt;
        }
    }

    for (const auto& guitar_adjustment : guitar.guitar_adjustments) {
        auto guitar_adjustment_update = guitar_adjustment;
        guitar_adjustment_update.guitar_id = guitar_id;
        const auto guitar_adjustment_id = add_guitar_adjustment(guitar_adjustment_update);
        if (!guitar_adjustment_id.has_value()) {
            return std::nullopt;
        }

        for (const auto& guitar_string_adjustment : guitar_adjustment.guitar_string_adjustments) {
            auto guitar_string_adjustment_update = guitar_string_adjustment;
            guitar_string_adjustment_update.guitar_adjustment_id = guitar_adjustment_id.value();
            if (!add_guitar_string_adjustment(guitar_string_adjustment_update).has_value()) {
                std::cerr << "Error while adding guitar_string_adjustment" << std::endl;
                return std::nullopt;
            }
        }
    }

    transaction.commit();
    return guitar_id;
}

bool GuitarDAOImpl::update_guitar(const GuitarRecord& guitar) {
    const std::string fret_markers = fretMarkersAsJson(guitar.fret_markers);
    const std::string sql = "UPDATE guitar SET name = ?, number_of_frets = ?, fret_markers = ?, type = ? WHERE id = ?";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar.name);
    query.bind(2, guitar.number_of_frets);
    query.bind(3, fret_markers);
    query.bind(4, guitar.type);
    query.bind(5, guitar.id.value());

    if (query.exec() != 1) {
        return false;
    }
    return true;
}

bool GuitarDAOImpl::delete_guitar(int32_t id) {
    SQLite::Transaction transaction(db);

    std::string guitarStringAdjustmentSql =
        "DELETE FROM guitar_string_adjustment WHERE guitar_adjustment_id IN (SELECT id FROM guitar_adjustment WHERE "
        "guitar_id=?)";
    SQLite::Statement guitarStringAdjustmentQuery(db, guitarStringAdjustmentSql);
    guitarStringAdjustmentQuery.bind(1, id);
    guitarStringAdjustmentQuery.exec();

    std::string guitarStringSql = "DELETE FROM guitar_string WHERE guitar_id=?";
    SQLite::Statement guitarStringQuery(db, guitarStringSql);
    guitarStringQuery.bind(1, id);
    guitarStringQuery.exec();

    std::string guitarAdjustmentSql = "DELETE FROM guitar_adjustment WHERE guitar_id=?";
    SQLite::Statement guitarAdjustmentQuery(db, guitarAdjustmentSql);
    guitarAdjustmentQuery.bind(1, id);
    guitarAdjustmentQuery.exec();

    const std::string sql = "DELETE FROM guitar WHERE id=?";
    SQLite::Statement guitarQuery(db, sql);
    guitarQuery.bind(1, id);
    guitarQuery.exec();

    transaction.commit();
    return true;
}

std::optional<int32_t> GuitarDAOImpl::add_guitar_string(const GuitarStringRecord& guitar_string_record) const {
    const std::string sql =
        "INSERT INTO guitar_string(guitar_id, string_number, start_note, octave) VALUES (?,?,?,?)";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_string_record.guitar_id);
    query.bind(2, guitar_string_record.string_number);
    query.bind(3, guitar_string_record.start_note);
    query.bind(4, guitar_string_record.octave);
    if (query.exec() != 1) {
        return std::nullopt;
    }
    return static_cast<int32_t>(db.getLastInsertRowid());
}

bool GuitarDAOImpl::update_guitar_string(const GuitarStringRecord& guitar_string_record) const {
    const std::string sql = "UPDATE guitar_string SET guitar_id=?, string_number=?, start_note=?, octave=? WHERE id=?";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_string_record.guitar_id);
    query.bind(2, guitar_string_record.string_number);
    query.bind(3, guitar_string_record.start_note);
    query.bind(4, guitar_string_record.octave);
    query.bind(5, guitar_string_record.id.value());

    return query.exec() == 1;
}

std::vector<GuitarStringRecord> GuitarDAOImpl::get_guitar_strings(int guitar_id) const {
    std::vector<GuitarStringRecord> strings;

    const std::string sql = "SELECT id, string_number, start_note, octave FROM guitar_string WHERE guitar_id=?";
    SQLite::Statement query(db, sql);
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

std::optional<int32_t> GuitarDAOImpl::add_guitar_adjustment(const GuitarAdjustmentRecord& guitar_adjustment_record
    ) const {
    const std::string sql =
        "INSERT INTO guitar_adjustment(guitar_id, name, position, \"order\") VALUES (?,?,?,?)";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_adjustment_record.guitar_id);
    query.bind(2, guitar_adjustment_record.name);
    query.bind(3, guitar_adjustment_record.position);
    query.bind(4, guitar_adjustment_record.order);

    if (query.exec() != 1) {
        return std::nullopt;
    }
    return static_cast<int32_t>(db.getLastInsertRowid());
}

bool GuitarDAOImpl::update_guitar_adjustment(const GuitarAdjustmentRecord& guitar_adjustment_record) const {
    const std::string sql = "UPDATE guitar_adjustment SET guitar_id=?, name=?, position=?, \"order\"=? WHERE id=?";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_adjustment_record.guitar_id);
    query.bind(2, guitar_adjustment_record.name);
    query.bind(3, guitar_adjustment_record.position);
    query.bind(4, guitar_adjustment_record.order);
    query.bind(5, guitar_adjustment_record.id.value());

    return query.exec() == 1;
}

std::vector<GuitarAdjustmentRecord> GuitarDAOImpl::get_guitar_adjustments(int guitar_id) const {
    std::vector<GuitarAdjustmentRecord> adjustments;

    const std::string sql = "SELECT id, name, position, \"order\" FROM guitar_adjustment WHERE guitar_id=?";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_id);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto position = query.getColumn(2).getInt();
        const auto order = query.getColumn(3).getInt();
        const auto string_adjustments = get_guitar_string_adjustments(id);
        adjustments.emplace_back(id, guitar_id, name, position, order, string_adjustments);
    }

    return adjustments;
}

std::optional<int32_t> GuitarDAOImpl::add_guitar_string_adjustment(
    const GuitarStringAdjustmentRecord& guitar_string_adjustment_record
    ) const {
    const std::string sql =
        "INSERT INTO guitar_string_adjustment(guitar_adjustment_id, string_number, step) VALUES (?,?,?)";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_string_adjustment_record.guitar_adjustment_id);
    query.bind(2, guitar_string_adjustment_record.string_number);
    query.bind(3, guitar_string_adjustment_record.step);

    if (query.exec() != 1) {
        return std::nullopt;
    }
    return static_cast<int32_t>(db.getLastInsertRowid());
}

bool GuitarDAOImpl::update_guitar_string_adjustment(const GuitarStringAdjustmentRecord& guitar_string_adjustment_record
    ) const {
    const std::string sql =
        "UPDATE guitar_string_adjustment SET guitar_adjustment_id=?, string_number=?, step=? WHERE id=?;";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_string_adjustment_record.guitar_adjustment_id);
    query.bind(2, guitar_string_adjustment_record.string_number);
    query.bind(3, guitar_string_adjustment_record.step);
    query.bind(4, guitar_string_adjustment_record.id.value());

    return query.exec() == 1;
}

std::vector<GuitarStringAdjustmentRecord> GuitarDAOImpl::get_guitar_string_adjustments(const int guitar_adjustment_id
    ) const {
    std::vector<GuitarStringAdjustmentRecord> string_adjustments;

    const std::string sql = "SELECT id, string_number, step FROM guitar_string_adjustment WHERE guitar_adjustment_id=?";
    SQLite::Statement query(db, sql);
    query.bind(1, guitar_adjustment_id);
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto string_number = query.getColumn(1).getInt();
        const auto step = query.getColumn(2).getInt();
        string_adjustments.emplace_back(id, guitar_adjustment_id, string_number, step);
    }

    return string_adjustments;
}

std::string GuitarDAOImpl::fretMarkersAsJson(const std::vector<int32_t>& fret_markers) {
    std::string fretMarkerString;
    if (fret_markers.empty()) {
        fretMarkerString = "[3, 5, 7, 9, 12, 15, 17, 19, 21]";
    } else {
        const nlohmann::json json_fret_markers = std::vector(fret_markers);
        fretMarkerString = json_fret_markers.dump();
    }
    return fretMarkerString;
}

std::vector<int32_t> GuitarDAOImpl::getFretMarkersFromJson(const std::string& fretMarkerString) {
    if (fretMarkerString.empty()) {
        return {};
    }
    auto fret_markers_json = nlohmann::json::parse(fretMarkerString);
    std::vector<int32_t> fret_markers(fret_markers_json.begin(), fret_markers_json.end());
    return fret_markers;
}

std::shared_ptr<GuitarDAO> GuitarDAO::create_guitar_dao(const std::shared_ptr<DatabaseConnection>& database) {
    auto* impl = dynamic_cast<DatabaseConnectionImpl*>(database.get());
    return std::make_shared<GuitarDAOImpl>(impl->getDatabase());
}
