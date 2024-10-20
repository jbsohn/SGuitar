//
// Created by John on 10/13/24.
//
#ifndef GUITAR_DAO_IMPL_H
#define GUITAR_DAO_IMPL_H

#include "guitar_record.hpp"
#include "guitar_DAO.hpp"

class GuitarDAOImpl final : public GuitarDAO {
    const SQLite::Database& db;

public:
    explicit GuitarDAOImpl(const SQLite::Database& database)
        : db(database) {
    }

    std::vector<GuitarRecord> get_guitars() override;
    void add_guitar(const GuitarRecord& guitar) override;
    int32_t update_guitar(const GuitarRecord& guitar) override;
    void delete_guitar(int32_t id) override;

protected:
    std::vector<GuitarStringRecord> get_guitar_strings(int guitar_id);
    std::vector<GuitarAdjustmentRecord> get_guitar_adjustments(int guitar_id);
    std::vector<GuitarStringAdjustmentRecord> get_guitar_string_adjustments(int guitar_adjustment_id);
};
#endif //GUITAR_DAO_IMPL_H
