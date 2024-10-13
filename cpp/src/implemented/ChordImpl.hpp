//
// Created by John on 10/13/24.
//

#ifndef CHORDIMPL_H
#define CHORDIMPL_H

#include "note_value.hpp"
#include "note.hpp"
#include "chord.hpp"

class ChordImpl final : public Chord {
    std::vector<NoteValue> notes;

public:
    ChordImpl(NoteValue root_note, const std::vector<int> &intervals);

    explicit ChordImpl(const std::vector<NoteValue> &notes) {
        this->notes = notes;
    }

    std::vector<NoteValue> get_notes() override {
        return notes;
    }

    std::string testDescription() override;

protected:
    static NoteValue note_for_interval(int interval, NoteValue rootNote);
};

#endif //CHORDIMPL_H
