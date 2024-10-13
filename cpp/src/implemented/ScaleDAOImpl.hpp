//
// Created by John on 10/13/24.
//

#ifndef SCALEDAOIMPL_H
#define SCALEDAOIMPL_H

#include "scale_record.hpp"
#include "scale_DAO.hpp"

class ScaleDAOImpl final : public ScaleDAO {
    const SQLite::Database &db;

public:
    explicit ScaleDAOImpl(const SQLite::Database &database) : db(database) {
    }

    std::vector<ScaleRecord> get_scales() override;

    void add_scale(const ScaleRecord &scale) override;

    void update_scale(int32_t id, const ScaleRecord &scale) override;

    void delete_scale(int32_t id) override;
};

#endif //SCALEDAOIMPL_H
