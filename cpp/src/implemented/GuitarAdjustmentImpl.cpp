//
//  GuitarAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <format>
#include <string>
#include <vector>
#include "guitar_adjustment.hpp"
#include "string_adjustment.hpp"

class GuitarAdjustmentImpl final : public GuitarAdjustment {
    std::string adjustment_name;
    std::vector<std::shared_ptr<StringAdjustment> > adjustments;
    bool activated = false;

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

    std::shared_ptr<StringAdjustment> string_adjustment_for_string_number(const int32_t string_number) override {
        for (auto &adjustment: adjustments) {
            if (adjustment->get_string_number() == string_number) {
                return adjustment;
            }
        }
        return nullptr;
    }

    bool is_activated() override {
        return activated;
    }

    void set_activated(const bool activated) override {
        this->activated = activated;
    }

    std::string testDescription() override {
        std::string description = std::format("adjustment_name: {}\n", adjustment_name);
        for (const auto &adjustment: adjustments) {
            description += std::format("{}\n", adjustment->testDescription());
        }
        return description;
    }
};

std::shared_ptr<GuitarAdjustment> GuitarAdjustment::create_with_adjustment_name(const std::string &adjustment_name) {
    return std::make_shared<GuitarAdjustmentImpl>(adjustment_name);
}
