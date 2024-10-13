//
//  Guitar.cpp
//  Guitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <format>
#include <vector>
#include <map>
#include "string_adjustment.hpp"
#include "GuitarImpl.hpp"

void GuitarImpl::reset_guitar(const std::vector<std::shared_ptr<Note> > &notes, const int32_t number_of_frets) {
    adjustments.clear();
    strings.clear();
    strings.push_back(GuitarString::create()); // "empty" string at index 0

    for (const auto &note: notes) {
        strings.push_back(GuitarString::create_with_start_note(note, number_of_frets));
    }
}

/** strings */
std::vector</*not-null*/ std::shared_ptr<GuitarString> > GuitarImpl::get_strings() {
    std::vector<std::shared_ptr<GuitarString> > s;
    s.assign(this->strings.begin() + 1, this->strings.end());
    return s;
}

void GuitarImpl::reset_strings() {
    for (const auto &string: strings) {
        string->reset();
    }
}

/** adjustment */
bool GuitarImpl::is_adjustment_activated(const std::string &adjustment_id) {
    if (const auto adjustment = adjustments[adjustment_id]; adjustment != nullptr) {
        return adjustment->is_activated();
    }
    return false;
}

void GuitarImpl::activate_adjustment(const std::string &adjustment_id, const bool activated) {
    if (const auto adjustment = adjustments[adjustment_id]; adjustment != nullptr) {
        for (const auto string_adjustments = adjustment->get_string_adjustments();
             const auto &stringAdjustment: string_adjustments) {
            const auto stringNumber = stringAdjustment->get_string_number();
            const auto step = activated ? stringAdjustment->get_step() : -stringAdjustment->get_step();
            const auto string = strings.at(stringNumber);
            string->adjust_string_by_steps(step);
        }
    }
}

/*not-null*/
std::shared_ptr<GuitarAdjustment> GuitarImpl::get_adjustment(const std::string &setting_id) {
    if (adjustments.contains(setting_id)) {
        return adjustments[setting_id];
    }
    return nullptr;
}

std::string GuitarImpl::testDescription() {
    std::string description;
    for (int string_number = 1; string_number < strings.size(); string_number++) {
        description += std::format("string {}: {}\n", string_number, strings[string_number]->testDescription());
    }
    return description;
}

std::shared_ptr<Guitar> Guitar::create() {
    return std::make_shared<GuitarImpl>();
}
