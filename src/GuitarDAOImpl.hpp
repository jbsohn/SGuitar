//
// Created by John Sohn on 10/13/24.
//
#ifndef GUITAR_DAO_IMPL_H
#define GUITAR_DAO_IMPL_H

#include "guitar_DAO.hpp"
#include "guitar_record.hpp"

class GuitarDAOImpl final : public GuitarDAO {
    SQLite::Database& db;

public:
    explicit GuitarDAOImpl(SQLite::Database& database) : db(database) {
    }

    std::vector<GuitarRecord> get_guitars() override;
    std::optional<int32_t> add_guitar(const GuitarRecord& guitar) override;
    bool update_guitar(const GuitarRecord& guitar) override;
    bool delete_guitar(int32_t id) override;

protected:
    [[nodiscard]] std::optional<int32_t> add_guitar_string(
        const GuitarStringRecord& guitar_string_record
    ) const;
    [[nodiscard]] bool update_guitar_string(
        const GuitarStringRecord& guitar_string_record
    ) const;
    [[nodiscard]] std::vector<GuitarStringRecord> get_guitar_strings(
        int guitar_id
    ) const;

    [[nodiscard]] std::optional<int32_t> add_guitar_adjustment(
        const GuitarAdjustmentRecord& guitar_adjustment_record
    ) const;
    [[nodiscard]] bool update_guitar_adjustment(
        const GuitarAdjustmentRecord& guitar_adjustment_record
    ) const;
    [[nodiscard]] std::vector<GuitarAdjustmentRecord> get_guitar_adjustments(
        int guitar_id
    ) const;

    [[nodiscard]] std::optional<int32_t> add_guitar_string_adjustment(
        const GuitarStringAdjustmentRecord& guitar_string_adjustment_record
    ) const;
    [[nodiscard]] bool update_guitar_string_adjustment(
        const GuitarStringAdjustmentRecord& guitar_string_adjustment_record
    ) const;
    [[nodiscard]] std::vector<GuitarStringAdjustmentRecord>
    get_guitar_string_adjustments(int guitar_adjustment_id) const;

    static std::string fretMarkersAsJson(
        const std::vector<int32_t>& fret_markers
    );
    static std::vector<int32_t> getFretMarkersFromJson(
        const std::string& fretMarkerString
    );
};
#endif  // GUITAR_DAO_IMPL_H
