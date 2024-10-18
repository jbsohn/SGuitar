//
// Created by John on 10/13/24.
//

#ifndef GUITAR_STRING_IMPL_H
#define GUITAR_STRING_IMPL_H

#include "note.hpp"
#include "guitar_string.hpp"

class GuitarStringImpl final : public GuitarString {
    std::vector<std::shared_ptr<Note>> notes;
    std::shared_ptr<Note> start_note;
    int number_of_fret;

public:
    GuitarStringImpl();
    GuitarStringImpl(const std::shared_ptr<Note>& start_note, int number_of_frets);

    std::shared_ptr<Note> get_start_note() override {
        return start_note;
    }

    std::vector<std::shared_ptr<Note>> get_notes() override {
        return notes;
    }

    void adjust_string_by_steps(int32_t steps) override;
    void reset() override { notes = string_with_start_note(start_note->get_midi_note(), number_of_fret); }
    std::string testDescription() override;

protected:
    static std::vector<std::shared_ptr<Note>> string_with_start_note(int midi_start_node, int number_of_frets);
};

#endif //GUITAR_STRING_IMPL_H
