//
//  GuitarAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include <vector>
#include <memory>
#include "guitar_adjustment.hpp"
#include "string_adjustment.hpp"

class GuitarAdjustmentImpl final : public GuitarAdjustment {
protected:
    std::string adjustmentID;
    std::vector<std::shared_ptr<StringAdjustment>> adjustments;
public:
    explicit GuitarAdjustmentImpl(const std::string &adjustmentID) {
        this->adjustmentID = adjustmentID;
    }

    std::string get_adjustment_id() override {
        return adjustmentID;
    }

    void clear_adjustments() override {
        adjustments.clear();
    }

    void add_string_adjustment(const std::shared_ptr<StringAdjustment> & adjustment) override {
        adjustments.push_back(adjustment);
    }

    std::vector<std::shared_ptr<StringAdjustment>> get_string_adjustments() override {
        return adjustments;
    } 

    std::shared_ptr<StringAdjustment> string_adjustment_for_string_number(int32_t string_number) override {
        for (auto & adjustment : adjustments) {
            if (adjustment->get_string_number() == string_number) {
                return adjustment;
            }
        }
        return nullptr;
    }

    std::string get_description() override {
        std::string description;
        description += "adjustmentID: ";
        description += adjustmentID;
        description += "\n";

        for (const auto& adjustment : adjustments) {
            description += "adjustment:";
            description += adjustment->get_description();
            description += "\n";
        }
        return description;
    }
};

std::shared_ptr<GuitarAdjustment> GuitarAdjustment::create_with_adjustment_id(const std::string & adjustment_id) {
    return std::make_shared<GuitarAdjustmentImpl>(adjustment_id);
}
