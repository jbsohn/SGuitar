//
//  Guitar.cpp
//  Guitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <iostream>
#include <fmt/format.h>
#include <vector>
#include "guitar_adjustment.hpp"
#include "string_adjustment.hpp"
#include "GuitarImpl.hpp"

GuitarImpl::GuitarImpl(const int32_t number_of_frets,
                       const std::vector<int>& fret_markers,
                       const std::vector<std::shared_ptr<GuitarString>>& guitar_strings,
                       const std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>>& guitar_adjustments
    ) {
    this->number_of_frets = number_of_frets;
    this->fret_markers = fret_markers;
    this->guitar_strings = guitar_strings;
    this->guitar_adjustments = guitar_adjustments;
}

/** strings */
std::vector<std::shared_ptr<GuitarString>> GuitarImpl::get_strings() {
    return guitar_strings;
}

void GuitarImpl::reset_strings() {
    for (const auto& string : guitar_strings) {
        string->reset();
    }
}

/** adjustment */
bool GuitarImpl::is_adjustment_activated(const std::string& adjustment_id) {
    if (const auto adjustment = guitar_adjustments[adjustment_id]; adjustment != nullptr) {
        return adjustment->is_activated();
    }
    return false;
}

void GuitarImpl::set_adjustment_activated(const std::string& adjustment_id, const bool activated) {
    if (const auto adjustment = guitar_adjustments[adjustment_id]; adjustment != nullptr) {
        for (const auto string_adjustments = adjustment->get_string_adjustments(); const auto& stringAdjustment :
             string_adjustments) {
            const auto stringNumber = stringAdjustment->get_string_number();
            const auto step = activated ? stringAdjustment->get_step() : -stringAdjustment->get_step();
            const auto string = guitar_strings.at(stringNumber);
            string->adjust_string_by_steps(step);
        }
    }
}

std::string GuitarImpl::test_description() {
    std::string description;
    for (int string_number = 1; string_number < guitar_strings.size(); string_number++) {
        description += fmt::format("string {}: {}\n", string_number, guitar_strings[string_number]->test_description());
    }

    for (const auto& [fst, snd] : guitar_adjustments) {
        description += fmt::format("{}:\n{}\n", fst, snd->test_description());
    }
    return description;
}

std::shared_ptr<Guitar> Guitar::create(int32_t number_of_frets,
                                       const std::vector<int32_t>& fret_markers,
                                       const std::vector<std::shared_ptr<GuitarString>>& guitar_strings,
                                       const std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>>&
                                       guitar_adjustments
    ) {
    return std::make_shared<GuitarImpl>(number_of_frets, fret_markers, guitar_strings, guitar_adjustments);
}
