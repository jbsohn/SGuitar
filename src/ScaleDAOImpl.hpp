//
// Created by John Sohn on 10/13/24.
//

#ifndef SCALE_DAO_IMPL_H
#define SCALE_DAO_IMPL_H

#include "scale_DAO.hpp"
#include "scale_record.hpp"

class ScaleDAOImpl final : public ScaleDAO {
    SQLite::Database& db;

public:
    explicit ScaleDAOImpl(SQLite::Database& database) : db(database) {
    }

    std::vector<ScaleRecord> get_scales() override;
    std::optional<int32_t> add_scale(const ScaleRecord& scale) override;
    bool update_scale(const ScaleRecord& scale) override;
    bool delete_scale(int32_t id) override;
};

#endif  // SCALE_DAO_IMPL_H
