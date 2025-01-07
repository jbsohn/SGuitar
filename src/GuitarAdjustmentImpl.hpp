//
// Created by John Sohn on 10/13/24.
//

#ifndef GUITAR_ADJUSTMENT_IMPL_H
#define GUITAR_ADJUSTMENT_IMPL_H

#include "guitar_adjustment.hpp"
#include "string_adjustment.hpp"

class GuitarAdjustmentImpl final : public GuitarAdjustment {
    std::vector<std::shared_ptr<StringAdjustment>> string_adjustments;
    int position;
    int order;
    bool activated = false;

public:
    explicit GuitarAdjustmentImpl(
        const std::vector<std::shared_ptr<StringAdjustment>>&
        string_adjustments,
        const int position,
        const int order
    ) {
        this->string_adjustments = string_adjustments;
        this->position = position;
        this->order = order;
    }

    std::vector<std::shared_ptr<StringAdjustment>>
    get_string_adjustments() override { return string_adjustments; }

    int32_t get_position() override { return position; }
    int32_t get_order() override { return order; }

    void set_activated(const bool activated) override {
        this->activated = activated;
    }

    bool is_activated() override { return activated; }
    std::string test_description() override;
};

#endif  // GUITAR_ADJUSTMENT_IMPL_H
