//
// Created by John Sohn on 10/13/24.
//

#ifndef GUITAR_IMPL_H
#define GUITAR_IMPL_H

#include "guitar.hpp"
#include "guitar_adjustment.hpp"
#include "guitar_string.hpp"

class GuitarImpl final : public Guitar {
    int number_of_frets = 0;
    std::vector<int> fret_markers;
    std::vector<std::shared_ptr<GuitarString>> guitar_strings;
    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>>
    guitar_adjustments;

public:
    GuitarImpl(
        int32_t number_of_frets,
        const std::vector<int>& fret_markers,
        const std::vector<std::shared_ptr<GuitarString>>& guitar_strings,
        const std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>>
        & guitar_adjustments
    );

    int32_t get_number_of_frets() override { return number_of_frets; }

    std::vector<int32_t> get_fret_markers() override { return fret_markers; }

    std::vector<std::shared_ptr<GuitarString>>
    get_strings() override;
    void reset_strings() override;

    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>>
    get_guitar_adjustments() override {
        return guitar_adjustments;
    }

    bool is_adjustment_activated(const std::string& adjustment_id) override;
    void set_adjustment_activated(
        const std::string& adjustment_id,
        bool activated
    ) override;

    std::string test_description() override;
};

#endif  // GUITAR_IMPL_H
