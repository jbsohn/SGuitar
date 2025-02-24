//
// Created by John Sohn on 10/13/24.
//

#ifndef NOTE_IMPL_H
#define NOTE_IMPL_H

#include <format>
#include "note.hpp"

class NoteImpl final : public Note {
    int midi_note = -1;

public:
    const static std::string note_names_sharp[];
    const static std::string note_names_flat[];

    NoteImpl(const NoteValue note, const int octave) {
        midi_note = (octave + 1) * 12 + static_cast<int>(note);
    }

    explicit NoteImpl(const int midi_note) { this->midi_note = midi_note; }
    int32_t get_midi_note() override { return midi_note; }

    NoteValue get_note() override {
        return static_cast<NoteValue>((midi_note - 12) % 12);
    }

    int32_t get_octave() override { return midi_note / 12 - 1; }

    std::string test_description() override {
        return format("{}", note_name_sharp());
    }

    std::string note_name_sharp() override {
        return note_names_sharp[static_cast<int>(get_note())];
    }

    std::string note_name_flat() override {
        return note_names_flat[static_cast<int>(get_note())];
    }
};

#endif  // NOTE_IMPL_H
