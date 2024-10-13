//
// Created by John on 10/13/24.
//

#ifndef SCALEIMPL_HPP
#define SCALEIMPL_HPP

#include "scale.hpp"

class ScaleImpl final : public Scale {
    std::string name;
    std::vector<NoteValue> notes;

public:
    ScaleImpl(NoteValue root_note, const std::vector<int> &semitones);

    std::vector<NoteValue> get_notes() override {
        return notes;
    }

    std::string testDescription() override;

protected:
    static NoteValue next_note_in_scale(NoteValue note, const int semitone);
};

#endif //SCALEIMPL_HPP
