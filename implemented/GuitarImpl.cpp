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
    int numberOfFrets = 0;
    std::vector<std::shared_ptr<GuitarString>> strings;
    std::map<std::string, std::shared_ptr<GuitarAdjustment>> adjustments;
    std::map<std::string, bool> settings;
public:
    GuitarImpl() {
        strings.clear();
        numberOfFrets = 0;
    }

    void reset() override {
        numberOfFrets = 0;
        strings.clear();
        adjustments.clear();
    }

    void set_number_of_frets(int32_t numberOfFrets) override {
        this->numberOfFrets = numberOfFrets;
    }

    int32_t get_number_of_frets() override {
        return numberOfFrets;
    }

    /** strings */
    std::vector</*not-null*/ std::shared_ptr<GuitarString>> get_strings() override {
        return strings;
    }

    void set_string(int32_t stringNumber, const /*not-null*/ std::shared_ptr<GuitarString> & guitarString) override {
        strings[stringNumber] = guitarString;
    }

    /*not-null*/ 
    std::shared_ptr<GuitarString> get_string(int32_t stringNumber) override {
        return strings[stringNumber];
    }

    void set_number_of_strings(int32_t numberOfStrings) override {
        strings.resize(numberOfStrings + 1);
    }

    int32_t get_number_of_strings() override {
        return static_cast<int32_t>(strings.size()) - 1;
    }

    /** adjustment */
    bool is_adjustment_enabled(const std::string & settingID) override {
        if (adjustments.contains(settingID)) {
            if (const auto adjustment = adjustments[settingID]; adjustment != nullptr) {
                return true;
            }
        }
        return false;
    }

    void activate_adjustment(const std::string & settingID, bool activated) override {
        if (const auto adjustment = adjustments[settingID]; adjustment != nullptr) {
            for (const auto stringAdjustments = adjustment->get_string_adjustments();
                 const auto& stringAdjustment : stringAdjustments ) {
                activateStringAdjustment(stringAdjustment, activated);
            }
            settings[settingID] = activated;
        }
    }

    void set_adjustment(const std::string & settingID, const /*not-null*/ std::shared_ptr<GuitarAdjustment> & adjustment) override {
        adjustments[settingID] = adjustment;
    }

    /*not-null*/ 
    std::shared_ptr<GuitarAdjustment> get_adjustment(const std::string & settingID) override {
        if (adjustments.contains(settingID)) {
            return adjustments[settingID];
        }
        return nullptr;
    }

    /** helpers */
    void resetStrings() override {
        for (int stringNumber = 1; stringNumber < strings.size(); stringNumber++) {
            auto string = strings.at(stringNumber);
            string.reset();
        }
    }

    bool is_adjustment_activated(const std::string & setting_id) override {
        return settings[setting_id];
    }

    std::vector<int32_t> string_numbers_adjusted(const std::string & setting_id) override {
        const auto adjustment = get_adjustment(setting_id);
        if (adjustment == nullptr) {
            return {};
        }

        std::vector<int> stringNumbers;
        for (const auto adjustments = adjustment->get_string_adjustments();
             const auto &stringAdjustment: adjustments) {
            int stringNumber = stringAdjustment->get_string_number();
            stringNumbers.push_back(stringNumber);
        }
        return stringNumbers;
    }

    NoteValue note_value(int32_t stringNumber, int32_t fret) override {
        const auto string = strings[stringNumber];
        const auto notes = string->get_midi_notes();
        const std::shared_ptr<Note> note = Note::create_with_midi_value(notes[fret]);
        return note->get_note_value();
    }

    int32_t midi_value(int32_t stringNumber, int32_t fret_number) override {
        if (stringNumber > 0 && fret_number >= 0) {
            const auto string = strings[stringNumber];
            const std::vector<int> notes = string->get_midi_notes();
            return notes[fret_number];
        }
        return -1;    }

    bool toggle_setting_id(const std::string & setting_id) override {
        auto activated = settings[setting_id];
        activated = !activated;
        activate_adjustment(setting_id, activated);
        return activated;
    }

    std::string get_description() override { 
        std::string description;

        for (int stringNumber = 1; stringNumber < strings.size(); stringNumber++) {
            const auto string = strings[stringNumber];
            std::vector<int> noteValues = string->get_midi_notes();
            const auto note = Note::create_with_midi_value(noteValues[0]);
            description += "string ";
            description += std::to_string(stringNumber);
            description += ": ";
            description += string->get_description();
            description += "\n";
        }
        return description;
    }
protected:
    void activateStringAdjustment(const std::shared_ptr<StringAdjustment>& adjustment, const bool enabled) const {
        const int stringNumber = adjustment->get_string_number();
        int step = 0;

        if (enabled) {
            step = adjustment->get_step();
        } else {
            step = -adjustment->get_step();
        }

        const auto string = strings.at(stringNumber);
        string->adjust_string_by_steps(step);
    }
};

/*not-null*/
std::shared_ptr<Guitar> Guitar::create() {
    return std::make_shared<GuitarImpl>();
}
