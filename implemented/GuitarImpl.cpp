//
//  Guitar.cpp
//  Guitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "guitar.hpp"

class GuitarImpl : public Guitar {
    std::vector<std::shared_ptr<GuitarString>> guitarStrings;
public:
    void reset() override {
        
    }

    void set_number_of_frets(int32_t numberOfFrets) override {
        
    }

    int32_t get_number_of_frets() override {
        return 0;
    }

    /** strings */
    std::vector</*not-null*/ std::shared_ptr<GuitarString>> get_strings() override {
        return guitarStrings;
    }

    void set_string(int32_t stringNumber, const /*not-null*/ std::shared_ptr<GuitarString> & guitarString) override {
        
    }

    /*not-null*/ 
    std::shared_ptr<GuitarString> get_string(int32_t stringNumber) override {
        return nullptr;
    }

    void set_number_of_strings(int32_t numberOfStrings) override {
        
    }

    int32_t get_number_of_strings() override {
        return 0;
    }

    /** adjustment */
    bool is_adjustment_enabled(const std::string & settingID) override {
        return false;
    }

    void activate_adjustment(const std::string & settingID, bool activated) override {
        
    }

    void set_adjustment(const std::string & settingID, const /*not-null*/ std::shared_ptr<GuitarAdjustment> & adjustment) override {
        
    }

    /*not-null*/ 
    std::shared_ptr<GuitarAdjustment> get_adjustment(const std::string & settingID) override {
        return nullptr;
    }

    /** helpers */
    void resetStrings() override {
        
    }

    bool is_adjustment_activated(const std::string & setting_id) override {
        return false;
    }

    std::vector<int32_t> string_numbers_adjusted(const std::string & setting_id) override {
        return std::vector<int32_t>();
    }

    int32_t note_value(int32_t stringNumber, int32_t fret) override {
        return 0;
    }

    int32_t midi_value(int32_t stringNumber, int32_t fret_number) override {
        return 0;
    }

    bool toggle_setting_id(const std::string & setting_id) override {
        return false;
    }

    std::string get_description() override { 
        return "";
    }
};

/*not-null*/
std::shared_ptr<Guitar> Guitar::create() {
    return std::make_shared<GuitarImpl>();
}

#if 0
namespace SG {
    struct Guitar::GuitarImpl {
        int numberOfFrets;
        std::vector<GuitarString> strings;
        std::map<std::string, GuitarAdjustment> adjustments;
        bool isValid;
        std::map<std::string, bool> settings;

        void init(const Guitar& guitar) {
            numberOfFrets = guitar.impl->numberOfFrets;
            strings = guitar.impl->strings;
            adjustments = guitar.impl->adjustments;
            isValid = guitar.impl->isValid;
            settings = guitar.impl->settings;
        }

        std::string readFile(std::string filename) {
            std::ifstream t(filename);
            std::stringstream buffer;
            buffer << t.rdbuf();
            return buffer.str();
        }
        
        void reset() {
            numberOfFrets { }
            strings.clear();
            adjustments.clear();
            isValid = false;
        }
        
        void activateStringAdjustment(const StringAdjustment& adjustment, bool enabled) {
            int stringNumber = adjustment.getStringNumber();
            int step { }
            
            if (enabled) {
                step = adjustment.getStep();
            } else {
                step = -(adjustment.getStep());
            }
            
            GuitarString& string = strings.at(stringNumber);
            string.adjustStringBySteps(step);
        }
        
        void resetString(int stringNumber) {
            GuitarString& string = strings.at(stringNumber);
            string.reset();
        }
        
        void printStringsAtFret0() {
            for (const GuitarString& string : strings) {
                if (string.isValid()) {
                    std::vector<int> noteValues = string.getNoteValues();
                    Note firstNote(noteValues[0]);
                }
            }
        }
    };

    Guitar::Guitar()
        : impl(new GuitarImpl) {
        impl->strings.clear();
        impl->numberOfFrets { }
        impl->isValid = false;
    }

    Guitar::~Guitar() {

    }


    bool Guitar::isValid() const {
        return impl->isValid;
    }

    void Guitar::reset() {
        impl->reset();
    }

    std::vector<GuitarString> Guitar::getStrings() const {
        return impl->strings;
    }

    void Guitar::setString(int stringNumber, GuitarString guitarString) {
        impl->strings[stringNumber] = guitarString;
    }

    GuitarString Guitar::getString(int stringNumber) const {
        return impl->strings[stringNumber];
    }
    
    void Guitar::setNumberOfStrings(int numberOfStrings) {
        impl->strings.resize(numberOfStrings + 1);
    }

    int Guitar::getNumberOfStrings() const {
        return (int) impl->strings.size() - 1;
    }

    void Guitar::setNumberOfFrets(int numberOfFrets) {
        impl->numberOfFrets = numberOfFrets;
    }

    int Guitar::getNumberOfFrets() const {
        return impl->numberOfFrets;
    }

    bool Guitar::isAdjustmentEnabled(std::string settingID) const {
        if (impl->adjustments.find(settingID) != impl->adjustments.end()) {
            GuitarAdjustment adjustment = impl->adjustments[settingID];
            return adjustment.isValid();
        }
        return false;
    }

    void Guitar::resetStrings() {
        for (int i = 1; i < impl->strings.size(); i++) {
            impl->resetString(i);
        }
    }

    void Guitar::activateAdjustment(std::string settingID, bool activated) {
        GuitarAdjustment adjustment = impl->adjustments[settingID];
        for (int i { } i < adjustment.getNumberOfStringAdjustments(); i++) {
            StringAdjustment curAdjustment = adjustment.getStringAdjustment(i);
            impl->activateStringAdjustment(curAdjustment, activated);
        }

        impl->settings[settingID] = activated;
    }
    
    void Guitar::setAdjustment(std::string settingID, GuitarAdjustment adjustment) {
        impl->adjustments[settingID] = adjustment;
    }

    std::optional<GuitarAdjustment> Guitar::getAdjustment(std::string settingID) const {
        if (impl->adjustments.contains(settingID)) {
            return impl->adjustments[settingID];
        }
        return {};
    }

    bool Guitar::isAdjustmentActivated(std::string settingID) const {
        return impl->settings[settingID];
    }

    std::vector<int> Guitar::stringNumbersAdjusted(std::string settingID) {
        auto adjustment = getAdjustment(settingID);
        if (!adjustment.has_value()) {
            return {};
        }

        std::vector<int> stringNumbers;
        for (int i { } i < adjustment.value().getNumberOfStringAdjustments(); i++) {
            StringAdjustment curStringAdjustment = adjustment.value().getStringAdjustment(i);
            int stringNumber = curStringAdjustment.getStringNumber();
            stringNumbers.push_back(stringNumber);
        }
        return stringNumbers;
    }
	
    int Guitar::noteValue(int stringNumber, int fret) {
        const GuitarString& string = impl->strings[stringNumber];
        std::vector<int> notes = string.getNoteValues();
        Note note(notes[fret]);
        return note.getNoteValue();
    }

    int Guitar::midiValue(int stringNumber, int fretNumber) {
        if (stringNumber > 0 && fretNumber >= 0) {
            const GuitarString& string = impl->strings[stringNumber];
            std::vector<int> notes = string.getNoteValues();
            return notes[fretNumber];
        }
        return -1;
    }

    bool Guitar::toggleSettingID(std::string settingID) {
        bool activated = isAdjustmentActivated(settingID);
        activated = !activated;
        activateAdjustment(settingID, activated);
        return activated;
    }

    std::string Guitar::getDescription() const {
        std::string description = "\r\n";
        for (int i { } i < impl->strings.size(); i++) {
            GuitarString curString = impl->strings[i];
            if (curString.isValid()) {
                std::vector<int> noteValues = curString.getNoteValues();
                Note curNote(noteValues[0]);
                description += "string ";
                description += std::to_string(i);
                description += ": ";
                description += NoteName::getNoteNameSharp(curNote.getNoteValue());
                description += "\r\n";
            }
        }
        return description;
    }
}
#endif
