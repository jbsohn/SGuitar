//
// Created by John on 10/13/24.
//

#include <SQLiteCpp/Database.h>
#include "GuitarDAOImpl.hpp"
#include "SGuitarDatabaseImpl.hpp"

std::vector<GuitarRecord> GuitarDAOImpl::get_guitars() {
    std::vector<GuitarRecord> guitars;

    SQLite::Statement query(
        db,
        "SELECT id, name, number_of_frets FROM guitar");

    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto number_of_frets = query.getColumn(2).getInt();
        const auto guitar_strings = get_guitar_strings(id);
        const auto guitar_adjustments = get_guitar_adjustments(id);
        guitars.emplace_back(id, name, number_of_frets, guitar_strings, guitar_adjustments);
    }

    return guitars;
}

void GuitarDAOImpl::add_guitar(const GuitarRecord& guitar) {
}

int32_t GuitarDAOImpl::update_guitar(const GuitarRecord& guitar) {
    return -1;
}

void GuitarDAOImpl::delete_guitar(int32_t id) {
}

// ReSharper disable once CppMemberFunctionMayBeConst
std::vector<GuitarStringRecord> GuitarDAOImpl::get_guitar_strings(int guitar_id) {
    std::vector<GuitarStringRecord> strings;

    SQLite::Statement query(
        db,
        "SELECT id, string_number, start_note, octave FROM guitar_string WHERE guitar_id=?");
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

std::vector<GuitarAdjustmentRecord> GuitarDAOImpl::get_guitar_adjustments(int guitar_id) {
    std::vector<GuitarAdjustmentRecord> adjustments;

    SQLite::Statement query(
        db,
        "SELECT id, name FROM guitar_adjustment WHERE guitar_id=?");
    query.bind(1, guitar_id);

    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto name = query.getColumn(1).getString();
        const auto string_adjustments = get_guitar_string_adjustments(id);
        adjustments.emplace_back(id, guitar_id, name, string_adjustments);
    }

    return adjustments;
}

// ReSharper disable once CppMemberFunctionMayBeConst
std::vector<GuitarStringAdjustmentRecord> GuitarDAOImpl::get_guitar_string_adjustments(const int guitar_adjustment_id) {
    std::vector<GuitarStringAdjustmentRecord> string_adjustments;

    SQLite::Statement query(
        db,
        "SELECT id, string_number, step FROM guitar_string_adjustment WHERE guitar_adjustment_id=?");
    query.bind(1, guitar_adjustment_id);

    while (query.executeStep()) {
        const auto id = query.getColumn(0).getInt();
        const auto string_number = query.getColumn(1).getInt();
        const auto step = query.getColumn(2).getInt();
        string_adjustments.emplace_back(id, guitar_adjustment_id, string_number, step);
    }

    return string_adjustments;
}

std::shared_ptr<GuitarDAO> GuitarDAO::create_guitar_dao(const std::shared_ptr<SGuitarDatabase>& database) {
    auto* impl = dynamic_cast<SGuitarDatabaseImpl*>(database.get());
    return std::make_shared<GuitarDAOImpl>(impl->getDatabase());
}
