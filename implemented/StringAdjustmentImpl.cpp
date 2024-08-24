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

class StringAdjustmentImpl : public StringAdjustment {
protected:
    int stringNumber;
    int step;
    bool valid;
public:
    StringAdjustmentImpl(int stringNumber, int step) {
        this->stringNumber = stringNumber;
        this->step = step;
        this->valid = true;
    }

    int32_t get_string_number() override {
        return stringNumber;
    }

    void set_step(int32_t step) override {
        this->step = step;
    }

    int32_t get_step() override {
        return step;
    }

    std::string get_description() override {
        std::string description = "";
        description += "stringNumber: ";
        description += std::to_string(stringNumber);
        description += ", step: ";
        description += std::to_string(step);
        description += ", isValid: ";
        description += std::to_string(valid);
        return description;
    }
};

 /*not-null*/
std::shared_ptr<StringAdjustment> StringAdjustment::create_with_string_number(int32_t string_number, int32_t step) {
    return std::make_shared<StringAdjustmentImpl>(string_number, step);
}
