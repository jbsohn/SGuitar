//
//  Scale.h
//  SGuitar
//
//  Created by John Sohn on 12/9/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#ifndef __Scale_h__
#define __Scale_h__

#include "Note.hpp"

#ifdef __cplusplus
#include <array>
#include <vector>

namespace SG {
    //
    // represents a Scale, given a root note value and a list of semitones
    //
    class Scale {
    protected:
        std::string name;
        std::vector<int> scaleNoteValues;
    public:
        Scale(int rootNoteValue, std::vector<int> semitones);
        std::vector<int> getNoteValues() const { return this->scaleNoteValues; }
        bool isNoteValueInScale(int noteValue) const;
        int intervalForNoteValue(int noteValue) const;
        std::string getDescription();
    protected:
        int nextNoteValueInScale(int noteValue, int semitone) const;
    };
}
#endif

#endif
