//
// Created by John Sohn on 10/13/24.
//

#ifndef SCALE_IMPL_HPP
#define SCALE_IMPL_HPP

#include "scale.hpp"

class ScaleImpl final : public Scale {
    std::string name;
    std::vector<NoteValue> notes;

public:
    ScaleImpl(NoteValue root_note, const std::vector<int>& semitones);
    std::vector<NoteValue> get_notes() override { return notes; }
    std::string test_description() override;

protected:
    static NoteValue next_note_in_scale(NoteValue note, int semitone);
};

#endif  // SCALE_IMPL_HPP
