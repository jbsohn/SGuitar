//
//  main.cpp
//  SGuitar
//
//  Created by John Sohn on 8/18/24.
//

#include <iostream>
#include "SG/Note.hpp"
#include "SG/NoteName.hpp"
#include "SG/Scale.hpp"
#include "SG/Chord.hpp"
#include "SG/GuitarString.hpp"
#include "SG/GuitarAdjustment.hpp"
#include "SG/Guitar.hpp"

int main(int argc, const char * argv[]) {
    auto note = SG::Note(3, 2);
    std::cout << "Note: " << note.getNoteNamePitchUTF8() << "\n";
    std::cout << "Name: " << SG::NoteName::nameForNoteValue(1, AT_SHARP) << "\n";
    
    std::vector<int> semitones = {2, 2, 1, 2, 2, 2};
    auto scale = SG::Scale(0, semitones);
    std::cout << "Scale: " << scale.getDescription() << "\n";

    std::vector<int> intervals = {0, 4, 7};
    auto chord = SG::Chord(0, intervals);
    std::cout << "Chord: " << chord.getDescription() << "\n";

    auto guitarString = SG::GuitarString(65, 13);
    std::cout << "GuitarString: " << guitarString.getDescription() << "\n";
    
    auto adjustment1 = SG::StringAdjustment(1, 1);
    auto adjustment2 = SG::StringAdjustment(2, 1);
    std::cout << "StringAdjustment 1: " << adjustment1.getDescription() << "\n";
    std::cout << "StringAdjustment 2: " << adjustment2.getDescription() << "\n";
    
    SG::GuitarAdjustment guitarAdjustment = SG::GuitarAdjustment("LKL");
    guitarAdjustment.addStringAdjustment(adjustment1);
    guitarAdjustment.addStringAdjustment(adjustment2);
    std::cout << "guitarAdjustment: " << guitarAdjustment.getDescription() << "\n";

    auto guitar = SG::Guitar();
    guitar.setNumberOfStrings(2);
    guitar.setString(1, guitarString);
    guitar.setString(2, guitarString);

    guitar.setAdjustment("LKL", guitarAdjustment);
    guitar.setAdjustment("A", guitarAdjustment);
    
    std::cout << "guitar: " << guitar.getDescription() << "\n";
    guitar.activateAdjustment("LKL", true);
    std::cout << "guitar: " << guitar.getDescription() << "\n";
    return 0;
}
