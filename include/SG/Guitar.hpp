//
//  Guitar.h
//  Guitar
//
//  Created by John Sohn on 12/9/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#ifndef __Guitar_h__
#define __Guitar_h__

#include "GuitarString.hpp"
#include "GuitarAdjustment.hpp"

#ifdef __cplusplus
#include <string>
#include <memory>
#include <optional>

namespace SG {
    //
    // - represents a guitar -- a collection of GuitarString, GuitarAdjustments
    // - read and writes a guitar from storage
    //
    class Guitar {
    public:
        Guitar();
        ~Guitar();
        
        bool isValid() const;
        void reset();
        void setNumberOfFrets(int numberOfFrets);
        int getNumberOfFrets() const;

        // strings
        std::vector<GuitarString> getStrings() const;
        void setString(int stringNumber, GuitarString guitarString);
        GuitarString getString(int stringNumber) const;
        void setNumberOfStrings(int numberOfStrings);
        int getNumberOfStrings() const;

        // adjustment
        bool isAdjustmentEnabled(std::string settingID) const;
        void activateAdjustment(std::string settingID, bool activated);
        void setAdjustment(std::string settingID, SG::GuitarAdjustment adjustment);
        std::optional<GuitarAdjustment> getAdjustment(std::string settingID) const;
        
        void resetStrings();
        bool isAdjustmentActivated(std::string settingID) const;
        std::vector<int> stringNumbersAdjusted(std::string settingID);
        int noteValue(int stringNumber, int fret);
        int midiValue(int stringNumber, int fretNumber);
        bool toggleSettingID(std::string settingID);
        std::string getDescription() const;
    private:
        struct GuitarImpl;
        std::unique_ptr<GuitarImpl> impl;
    };
}
#endif

#endif
