//
// Created by John on 10/13/24.
//

#ifndef STRINGADJUSTMENTIMPL_H
#define STRINGADJUSTMENTIMPL_H

#include <format>
#include "string_adjustment.hpp"

class StringAdjustmentImpl final : public StringAdjustment {
    int string_number;
    int step;

public:
    StringAdjustmentImpl(const int stringNumber, const int step);

    int32_t get_string_number() override {
        return string_number;
    }

    void set_step(const int32_t step) override {
        this->step = step;
    }

    int32_t get_step() override {
        return step;
    }

    std::string testDescription() override {
        return std::format("string_number: {}, step={}", string_number, step);
    }
};

#endif //STRINGADJUSTMENTIMPL_H
