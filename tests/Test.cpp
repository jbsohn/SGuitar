#include <iostream>
#include "note.hpp"
#include "note_value.hpp"

void testNote() {
    const auto note = Note::create_with_note_value(NoteValue::C, 2);
    std::cout << "Note: " << note->get_description() << "\n";
    std::cout << "Name: " << note->get_description() << "\n";
}

int main () {
    testNote();
    return 0;
}