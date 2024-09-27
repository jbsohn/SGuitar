//
//  StringAdjustment.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <string>
#include <memory>
#include "string_adjustment.hpp"

class StringAdjustmentImpl final : public StringAdjustment {
    int string_number;
    int step;

public:
    StringAdjustmentImpl(const int stringNumber, const int step) {
        this->string_number = stringNumber;
        this->step = step;
    }

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
        std::string description;
        description += "string_number: ";
        description += std::to_string(string_number);
        description += ", step: ";
        description += std::to_string(step);
        return description;
    }
};

std::shared_ptr<StringAdjustment> StringAdjustment::create_with_string_number(int32_t string_number, int32_t step) {
    return std::make_shared<StringAdjustmentImpl>(string_number, step);
}
