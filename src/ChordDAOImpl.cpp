//
// Created by John Sohn on 10/13/24.
//

#include <nlohmann/json.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include "SGuitarDatabaseImpl.hpp"
#include "ChordDAOImpl.hpp"

std::vector<ChordRecord> ChordDAOImpl::get_chords() {
    std::vector<ChordRecord> chords;

    SQLite::Statement query(db, "SELECT id, name, intervals FROM chord");
    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        auto intervals_json = nlohmann::json::parse(query.getColumn(2).getString());
        std::vector<int32_t> intervals(intervals_json.begin(), intervals_json.end());
        chords.emplace_back(id, name, intervals);
    }

    return chords;
}

std::optional<int32_t> ChordDAOImpl::add_chord(const ChordRecord& chord) {
    const nlohmann::json json_intervals = std::vector(chord.intervals);

    SQLite::Statement query(db, "INSERT INTO chord (name, intervals) VALUES (?, ?) RETURNING id");
    query.bind(1, chord.name);
    query.bind(2, json_intervals.dump());
    if (query.executeStep()) {
        return query.getColumn(0).getInt();
    }
    return std::nullopt;
}

bool ChordDAOImpl::update_chord(const ChordRecord& chord) {
    const nlohmann::json json_intervals = std::vector(chord.intervals);

    SQLite::Statement query(db, "UPDATE chord SET name = ?, intervals = ? WHERE id=?");
    query.bind(1, chord.name);
    query.bind(2, json_intervals.dump());
    query.bind(3, chord.id.value());
    if (query.exec() != 1) {
        return false;
    }
    return true;
}

bool ChordDAOImpl::delete_chord(const int32_t id) {
    SQLite::Statement query(db, "DELETE FROM chord WHERE id=?");
    query.bind(1, id);
    return true;
}

std::shared_ptr<ChordDAO> ChordDAO::create_chord_dao(const std::shared_ptr<SGDatabaseConnection>& database) {
    auto* impl = dynamic_cast<SGDatabaseConnectionImpl*>(database.get());
    return std::make_shared<ChordDAOImpl>(impl->getDatabase());
}
