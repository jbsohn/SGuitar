//
// Created by John on 10/13/24.
//

#ifndef STRING_ADJUSTMENT_IMPL_H
#define STRING_ADJUSTMENT_IMPL_H

#include "string_adjustment.hpp"

class StringAdjustmentImpl final : public StringAdjustment {
    int string_number;
    int step;

public:
    StringAdjustmentImpl(int string_number, int step);
    int32_t get_string_number() override { return string_number; }
    int32_t get_step() override { return step; }
    std::string test_description() override;
};

#endif  // STRING_ADJUSTMENT_IMPL_H
