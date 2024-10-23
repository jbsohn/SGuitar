//
//  StringAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include "StringAdjustmentImpl.hpp"

StringAdjustmentImpl::StringAdjustmentImpl(const int string_number, const int step) {
    this->string_number = string_number;
    this->step = step;
}

std::shared_ptr<StringAdjustment> StringAdjustment::create_with_string_number(int32_t string_number, int32_t step) {
    return std::make_shared<StringAdjustmentImpl>(string_number, step);
}
