//
//  GuitarAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <fmt/format.h>
#include <string>
#include "GuitarAdjustmentImpl.hpp"

std::string GuitarAdjustmentImpl::test_description() {
    std::string description;
    for (const auto& adjustment : string_adjustments) {
        description += fmt::format("{}\n", adjustment->test_description());
    }
    return description;
}

std::shared_ptr<GuitarAdjustment> GuitarAdjustment::create_with_string_adjustments(
    const std::vector<std::shared_ptr<StringAdjustment>>& string_adjustments,
    int position,
    int order
    ) {
    return std::make_shared<GuitarAdjustmentImpl>(string_adjustments, position, order);
}
