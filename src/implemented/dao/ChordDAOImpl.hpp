//
// Created by John on 10/13/24.
//

#ifndef CHORD_DAO_IMPL_H
#define CHORD_DAO_IMPL_H

#include "chord_DAO.hpp"
#include "chord_record.hpp"

class ChordDAOImpl final : public ChordDAO {
    const SQLite::Database& db;

public:
    explicit ChordDAOImpl(const SQLite::Database& database) : db(database) {}
    std::vector<ChordRecord> get_chords() override;
    int32_t add_chord(const ChordRecord& chord) override;
    void update_chord(const ChordRecord& chord) override;
    void delete_chord(int32_t id) override;
};

#endif  // CHORD_DAO_IMPL_H
