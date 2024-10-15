//
// Created by John on 10/14/24.
//

#include "SGuitarFactory.hpp"

#include <note.hpp>

#include "string_adjustment.hpp"
#include "guitar_adjustment.hpp"
#include "guitar.hpp"
#include "guitar_string.hpp"

std::shared_ptr<Guitar> SGuitarFactory::createGuitar(const GuitarRecord &guitar_record) {
    std::vector<std::shared_ptr<GuitarString> > guitar_strings;
    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment> > guitar_adjustments;

    for (const auto guitar_string: guitar_record.guitar_strings) {
        auto note = Note::create_with_midi_note(48);
        guitar_strings.push_back(GuitarString::create_with_start_note(note, guitar_record.number_of_frets));
    }

    for (const auto &guitar_adjustment: guitar_record.guitar_adjustments) {
        auto guitarAdjustment = GuitarAdjustment::create_with_name(guitar_adjustment.name);

        for (auto guitar_string_adjustment: guitar_adjustment.guitar_string_adjustments) {
            auto adjustment = StringAdjustment::create_with_string_number(
                guitar_string_adjustment.string_number,
                guitar_string_adjustment.step);
            guitarAdjustment->add_string_adjustment(adjustment);
        }
    }

    return Guitar::create(
        guitar_record.number_of_frets,
        guitar_strings,
        guitar_adjustments);
}

std::shared_ptr<Guitar> SGuitarFactory::createScale(const ScaleRecord &scale_record) {
    return nullptr;
}

std::shared_ptr<Guitar> SGuitarFactory::createChord(const ChordRecord &chord_record) {
    return nullptr;
}
