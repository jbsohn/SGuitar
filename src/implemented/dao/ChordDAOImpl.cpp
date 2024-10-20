//
// Created by John on 10/13/24.
//

#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>
#include "ChordDAOImpl.hpp"
#include "SGuitarDatabaseImpl.hpp"

std::vector<ChordRecord> ChordDAOImpl::get_chords() {
    std::vector<ChordRecord> chords;

    SQLite::Statement query(
        db,
        "SELECT id, name, intervals FROM chord");

    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        auto intervals_json = nlohmann::json::parse(query.getColumn(2).getString());
        std::vector<int32_t> intervals(intervals_json.begin(), intervals_json.end());
        chords.emplace_back(id, name, intervals);
    }

    return chords;
}

int32_t ChordDAOImpl::add_chord(const ChordRecord& chord) {
    const nlohmann::json json_intervals = std::vector(chord.intervals);
    int32_t id = -1;

    SQLite::Statement query(
        db,
        "INSERT INTO chord (name, intervals) VALUES (?, ?) RETURNING id");
    query.bind(1, chord.name);
    query.bind(2, json_intervals.dump());

    if (query.executeStep()) {
        id = query.getColumn(0).getInt();
    }
    return id;
}

void ChordDAOImpl::update_chord(const ChordRecord& chord) {
    const nlohmann::json json_intervals = std::vector(chord.intervals);

    SQLite::Statement query(
        db,
        "UPDATE chord SET name = ?, intervals = ? WHERE id=?");
    query.bind(1, chord.name);
    query.bind(2, json_intervals.dump());
    query.bind(3, chord.id);

    query.exec();
}

void ChordDAOImpl::delete_chord(const int32_t id) {
    SQLite::Statement query(
        db,
        "DELETE FROM chord WHERE id=?");
    query.bind(1, id);

    query.exec();
}

std::shared_ptr<ChordDAO> ChordDAO::create_chord_dao(const std::shared_ptr<SGuitarDatabase>& database) {
    auto* impl = dynamic_cast<SGuitarDatabaseImpl*>(database.get());
    return std::make_shared<ChordDAOImpl>(impl->getDatabase());
}
