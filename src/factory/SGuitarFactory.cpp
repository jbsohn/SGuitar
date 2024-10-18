//
// Created by John on 10/14/24.
//

#include "SGuitarFactory.hpp"

#include "note.hpp"
#include "string_adjustment.hpp"
#include "guitar_adjustment.hpp"
#include "guitar_string.hpp"
#include "guitar.hpp"

std::shared_ptr<Guitar> SGuitarFactory::createGuitar(const GuitarRecord& guitar_record) {
    std::vector<std::shared_ptr<GuitarString>> guitar_strings;
    guitar_strings.resize(max_string_number(guitar_record) + 1);

    for (const auto& guitar_string : guitar_record.guitar_strings) {
        const auto note_value = Note::note_value_for_note_string(guitar_string.start_note);
        const auto note = Note::create_with_note(note_value, guitar_string.octave);
        guitar_strings[guitar_string.string_number] = GuitarString::create_with_start_note(
            note, guitar_record.number_of_frets);
    }
    create_missing_guitar_strings(guitar_strings);

    const std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>> guitar_adjustments;
    for (const auto& guitar_adjustment : guitar_record.guitar_adjustments) {
        const auto guitarAdjustment = GuitarAdjustment::create_with_name(guitar_adjustment.name);
        for (const auto& guitar_string_adjustment : guitar_adjustment.guitar_string_adjustments) {
            auto adjustment = StringAdjustment::create_with_string_number(
                guitar_string_adjustment.string_number,
                guitar_string_adjustment.step);
            guitarAdjustment->add_string_adjustment(adjustment);
        }
    }

    return Guitar::create(guitar_record.number_of_frets, guitar_strings, guitar_adjustments);
}

std::shared_ptr<Scale> SGuitarFactory::createScale(const NoteValue root_note, const ScaleRecord& scale_record) {
    return Scale::create_with_root_note(root_note, scale_record.semitones);
}

std::shared_ptr<Chord> SGuitarFactory::createChord(const NoteValue root_note, const ChordRecord& chord_record) {
    return Chord::create_with_root_note(root_note, chord_record.intervals);
}

int SGuitarFactory::max_string_number(const GuitarRecord& guitar_record) {
    int max_string_number = 0;

    for (const auto& guitar_string : guitar_record.guitar_strings) {
        if (guitar_string.string_number > max_string_number) {
            max_string_number = guitar_string.string_number;
        }
    }

    return max_string_number;
}

void SGuitarFactory::create_missing_guitar_strings(std::vector<std::shared_ptr<GuitarString>>& guitar_strings) {
    for (auto& guitar_string : guitar_strings) {
        if (guitar_string == nullptr) {
            guitar_string = GuitarString::create();
        }
    }
}