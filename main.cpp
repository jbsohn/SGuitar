//
//  main.cpp
//  SGuitar
//
//  Created by John Sohn on 8/18/24.
//

#include <iostream>
#include "note_value.hpp"
#include "string_adjustment.hpp"
#include "note.hpp"
#include "scale.hpp"
#include "chord.hpp"
#include "guitar_string.hpp"
#include "guitar_adjustment.hpp"
#include "guitar.hpp"

int main(int argc, const char * argv[]) {
    const auto note = Note::create_with_note_value(3, 2);
    std::cout << "Note: " << note->get_description() << "\n";
    std::cout << "Name: " << note->get_description() << "\n";

    const auto semitones = {2, 2, 1, 2, 2, 2};
    const auto scale = Scale::create_with_root_note_value(NoteValue::C, semitones);
    std::cout << "Scale: " << scale->get_description() << "\n";

    const auto intervals = {0, 4, 7};
    const auto chord = Chord::create_with_root_note_value(NoteValue::C, intervals);
    std::cout << "Chord: " << chord->get_description()  << "\n";

    const auto guitarString = GuitarString::create_with_midi_start_value(65, 13);
    std::cout << "GuitarString: " << guitarString->get_description() << "\n";

    const auto adjustment1 = StringAdjustment::create_with_string_number(1, 1);
    const auto adjustment2 = StringAdjustment::create_with_string_number(2, 1);
    std::cout << "StringAdjustment 1: " << adjustment1->get_description() << "\n";
    std::cout << "StringAdjustment 2: " << adjustment2->get_description() << "\n";

    const auto guitarAdjustment = GuitarAdjustment::create_with_adjustment_id("LKL");
    guitarAdjustment->add_string_adjustment(adjustment1);
    guitarAdjustment->add_string_adjustment(adjustment2);
    std::cout << "guitarAdjustment: " << guitarAdjustment->get_description() << "\n";

    auto guitar = Guitar::create();
    guitar->set_number_of_strings(2);
    guitar->set_string(1, guitarString);
    guitar->set_string(2, guitarString);

    guitar->set_adjustment("LKL", guitarAdjustment);
    guitar->set_adjustment("A", guitarAdjustment);

    std::cout << "guitar: " << guitar->get_description() << "\n";
    guitar->activate_adjustment("LKL", true);
    std::cout << "guitar: " << guitar->get_description() << "\n";
    return 0;
}
