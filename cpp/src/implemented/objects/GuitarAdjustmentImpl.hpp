//
// Created by John on 10/13/24.
//

#ifndef GUITARADJUSTMENTIMPL_H
#define GUITARADJUSTMENTIMPL_H

#include "guitar_adjustment.hpp"
#include "string_adjustment.hpp"

class GuitarAdjustmentImpl final : public GuitarAdjustment {
    std::string adjustment_name;
    std::vector<std::shared_ptr<StringAdjustment> > adjustments;
    bool adjustment_activated = false;

public:
    explicit GuitarAdjustmentImpl(const std::string &adjustment_name) {
        this->adjustment_name = adjustment_name;
    }

    std::string get_adjustment_name() override {
        return adjustment_name;
    }

    void clear_adjustments() override {
        adjustments.clear();
    }

    void add_string_adjustment(const std::shared_ptr<StringAdjustment> &adjustment) override {
        adjustments.push_back(adjustment);
    }

    std::vector<std::shared_ptr<StringAdjustment> > get_string_adjustments() override {
        return adjustments;
    }

    std::shared_ptr<StringAdjustment> string_adjustment_for_string_number(int32_t string_number) override;

    bool is_activated() override {
        return adjustment_activated;
    }

    void set_activated(const bool activated) override {
        adjustment_activated = activated;
    }

    std::string testDescription() override;
};

#endif //GUITARADJUSTMENTIMPL_H
