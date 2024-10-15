//
//  GuitarAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <format>
#include <string>
#include "GuitarAdjustmentImpl.hpp"

std::shared_ptr<StringAdjustment>
GuitarAdjustmentImpl::string_adjustment_for_string_number(const int32_t string_number) {
    for (auto &adjustment: adjustments) {
        if (adjustment->get_string_number() == string_number) {
            return adjustment;
        }
    }
    return nullptr;
}

std::string GuitarAdjustmentImpl::testDescription() {
    std::string description = std::format("adjustment_name: {}\n", name);
    for (const auto &adjustment: adjustments) {
        description += std::format("{}\n", adjustment->testDescription());
    }
    return description;
}

std::shared_ptr<GuitarAdjustment> GuitarAdjustment::create_with_name(const std::string &name) {
    return std::make_shared<GuitarAdjustmentImpl>(name);
}
