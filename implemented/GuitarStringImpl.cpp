//
//  GuitarString.cpp
//  SGuitar
//
//  Created by John Sohn on 12/14/14.
//  Copyright (c) 2014 John Sohn. All rights reserved.
//

#include <vector>
#include "guitar_string.hpp"
#include "note.hpp"
#include "note_value.hpp"

class NoteImpl;

class GuitarStringImpl : public GuitarString {
protected:
    std::vector<int> midiNoteValues;
    int startNoteMidiValue;
    int numberOfFrets;
public:
    GuitarStringImpl(int midiValue, int numberOfFrets) {
        midiNoteValues.resize(numberOfFrets);
        this->startNoteMidiValue = midiValue;
        this->numberOfFrets = numberOfFrets;
        reset();
    }


    int32_t get_start_note_midi_value() override {
        return startNoteMidiValue;
    }

    std::vector<int32_t> get_midi_notes() override {
        return midiNoteValues;
    }

    void reset() override {
        midiNoteValues.resize(numberOfFrets + 1);
        int curNoteMIDIValue = startNoteMidiValue;

        for (int fret = 0; fret <= numberOfFrets; fret++) {
            midiNoteValues[fret] = curNoteMIDIValue;
            curNoteMIDIValue++;
        }
    }

    void adjust_string_by_steps(int32_t steps) override {
        for (int fret = 0; fret <= numberOfFrets; fret++) {
            int curNoteMIDIValue = midiNoteValues[fret];
            curNoteMIDIValue += steps;
            midiNoteValues[fret] = curNoteMIDIValue;
        }
    }

    std::string get_description() override {
        static std::string s = "";
        bool first = true;
        for (int midiNoteValue : midiNoteValues) {
            if (!first) {
                s += " ";
                first = false;
            }
            s += " ";
            s += midiNoteValue;
            s += "";
        }
        return s;
    }
};

/*not-null*/
std::shared_ptr<GuitarString> GuitarString::create_with_midi_start_value(int32_t midi_start_value, int32_t number_of_frets) {
    return std::make_shared<GuitarStringImpl>(midi_start_value, number_of_frets);
}
