//
// Created by John on 10/13/24.
//

#ifndef CHORD_IMPL_H
#define CHORD_IMPL_H

#include "note_value.hpp"
#include "note.hpp"
#include "chord.hpp"

class ChordImpl final : public Chord {
    std::vector<NoteValue> notes;

public:
    ChordImpl(NoteValue root_note, const std::vector<int>& intervals);

    explicit ChordImpl(const std::vector<NoteValue>& notes) {
        this->notes = notes;
    }

    std::vector<NoteValue> get_notes() override {
        return notes;
    }

    std::string test_description() override;

protected:
    static NoteValue note_for_interval(int interval, NoteValue rootNote);
};

#endif //CHORD_IMPL_H
