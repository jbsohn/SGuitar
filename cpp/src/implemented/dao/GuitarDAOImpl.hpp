//
// Created by John on 10/13/24.
//

#ifndef GUITARDAOIMPL_H
#define GUITARDAOIMPL_H

#include <guitar_string.hpp>
#include <SQLiteCpp/Database.h>
#include "guitar_record.hpp"
#include "guitar_DAO.hpp"

class GuitarDAOImpl final : public GuitarDAO {
    const SQLite::Database &db;

public:
    explicit GuitarDAOImpl(const SQLite::Database &database) : db(database) {
    }

    std::vector<GuitarRecord> get_guitars() override;

    void add_guitar(const GuitarRecord &guitar) override;

    int32_t update_guitar(const GuitarRecord &guitar) override;

    void delete_guitar(int32_t id) override;

protected:
    std::vector<GuitarRecord> get_guitar_records();

    std::vector<GuitarStringRecord> get_guitar_strings(int guitar_id) const;

    std::vector<GuitarAdjustmentRecord> get_guitar_adjustments(int guitar_id);

    std::vector<GuitarStringAdjustmentRecord> get_guitar_string_adjustments(int guitar_adjustment_id);
};

#endif //GUITARDAOIMPL_H
