//
//  Guitar.cpp
//  Guitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <fstream>
#include <vector>
#include <map>
#include "guitar_adjustment.hpp"
#include "guitar_string.hpp"
#include "note.hpp"
#include "guitar.hpp"
#include "string_adjustment.hpp"

class GuitarImpl final : public Guitar {
    int number_of_frets = 0;
    std::vector<std::shared_ptr<GuitarString> > strings;
    std::map<std::string, std::shared_ptr<GuitarAdjustment> > adjustments;
    std::map<std::string, bool> settings;

public:
    GuitarImpl() = default;

    void reset_guitar(const std::vector<std::shared_ptr<Note> > &notes, const int32_t number_of_frets) override {
        strings.clear();
        strings.push_back(GuitarString::create()); // "empty" string at index 0

        for (const auto &note: notes) {
            strings.push_back(GuitarString::create_with_start_note(note, number_of_frets));
        }
    }

    /** strings */
    std::vector</*not-null*/ std::shared_ptr<GuitarString> > get_strings() override {
        std::vector<std::shared_ptr<GuitarString> > s;
        s.assign(this->strings.begin() + 1, this->strings.end());
        return s;
    }

    void reset_strings() override {
        for (const auto &string: strings) {
            string->reset();
        }
    }

    /** adjustment */
    bool is_adjustment_enabled(const std::string &setting_id) override {
        if (adjustments.contains(setting_id)) {
            if (const auto adjustment = adjustments[setting_id]; adjustment != nullptr) {
                return true;
            }
        }
        return false;
    }

    void activate_adjustment(const std::string &setting_id, const bool activated) override {
        if (const auto adjustment = adjustments[setting_id]; adjustment != nullptr) {
            for (const auto string_adjustments = adjustment->get_string_adjustments();
                 const auto &stringAdjustment: string_adjustments) {
                const auto stringNumber = stringAdjustment->get_string_number();
                const auto step = activated ? stringAdjustment->get_step() : -stringAdjustment->get_step();
                const auto string = strings.at(stringNumber);
                string->adjust_string_by_steps(step);
            }
            settings[setting_id] = activated;
        }
    }

    void set_adjustment(const std::string &setting_id,
                        const /*not-null*/ std::shared_ptr<GuitarAdjustment> &adjustment) override {
        adjustments[setting_id] = adjustment;
    }

    /*not-null*/
    std::shared_ptr<GuitarAdjustment> get_adjustment(const std::string &setting_id) override {
        if (adjustments.contains(setting_id)) {
            return adjustments[setting_id];
        }
        return nullptr;
    }

    std::string testDescription() override {
        std::string description;

        for (int string_number = 1; string_number < strings.size(); string_number++) {
            const auto string = strings[string_number];
            description += "string ";
            description += std::to_string(string_number);
            description += ": ";
            description += string->testDescription();
            description += "\n";
        }
        return description;
    }
};

/*not-null*/
std::shared_ptr<Guitar> Guitar::create() {
    return std::make_shared<GuitarImpl>();
}
