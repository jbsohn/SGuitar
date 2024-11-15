//
// Created by John Sohn on 11/14/24.
//

#include <doctest/doctest.h>
#include <chord.hpp>
#include "note_value.hpp"
#include "note.hpp"

TEST_CASE("Testing the Note object") {
    const std::shared_ptr<Note> note = Note::create_with_note(NoteValue::C, 2);
    CHECK(note->get_octave() == 2);
    CHECK(note->get_note() == NoteValue::C);
    CHECK(note->get_midi_note() == 36);
}
