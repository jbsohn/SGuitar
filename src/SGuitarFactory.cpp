//
// Created by John on 10/14/24.
//

#include <GuitarAdjustmentImpl.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include "chord.hpp"
#include "chord_record.hpp"
#include "guitar.hpp"
#include "guitar_adjustment.hpp"
#include "guitar_adjustment_record.hpp"
#include "guitar_record.hpp"
#include "guitar_string.hpp"
#include "note.hpp"
#include "note_value.hpp"
#include "scale.hpp"
#include "scale_record.hpp"
#include "SGuitar_factory.hpp"
#include "string_adjustment.hpp"
#include "guitar_string_adjustment_record.hpp"

int max_string_number(const std::vector<GuitarStringRecord>& guitar_strings_records) {
    int max_string_number = 0;
    for (const auto& guitar_string : guitar_strings_records) {
        if (guitar_string.string_number > max_string_number) {
            max_string_number = guitar_string.string_number;
        }
    }
    return max_string_number;
}

std::vector<std::shared_ptr<GuitarString>> create_guitar_strings(const int number_of_frets,
                                                                 const std::vector<GuitarStringRecord>&
                                                                 guitar_strings_records
    ) {
    std::vector<std::shared_ptr<GuitarString>> guitar_strings;
    guitar_strings.resize(max_string_number(guitar_strings_records) + 1);

    for (const auto& guitar_string_record : guitar_strings_records) {
        const auto note_value = Note::note_value_for_note_string(guitar_string_record.start_note);
        const auto note = Note::create_with_note(note_value, guitar_string_record.octave);
        guitar_strings[guitar_string_record.string_number] =
            GuitarString::create_with_start_note(note, number_of_frets);
    }

    // ensure an empty guitar string is created for objects in range of array if not defined
    for (auto& guitar_string : guitar_strings) {
        if (guitar_string == nullptr) {
            guitar_string = GuitarString::create();
        }
    }

    return guitar_strings;
}

std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>> create_guitar_adjustments(
    const std::vector<GuitarAdjustmentRecord>& guitar_adjustment_records
    ) {
    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment>> guitar_adjustments;

    for (const auto& guitar_adjustment_record : guitar_adjustment_records) {
        std::vector<std::shared_ptr<StringAdjustment>> string_adjustments;

        for (const auto& guitar_string_adjustment : guitar_adjustment_record.guitar_string_adjustments) {
            const auto adjustment = StringAdjustment::create_with_string_number(guitar_string_adjustment.string_number,
                    guitar_string_adjustment.step
                );
            string_adjustments.push_back(adjustment);
        }

        guitar_adjustments[guitar_adjustment_record.name] = GuitarAdjustment::create_with_string_adjustments(
            string_adjustments
            );
    }

    std::cout << guitar_adjustments["P1"]->test_description() << std::endl;
    return guitar_adjustments;
}

std::shared_ptr<Guitar> SGuitarFactory::create_guitar(const GuitarRecord& guitar_record) {
    const auto strings = create_guitar_strings(guitar_record.number_of_frets, guitar_record.guitar_strings);
    const auto adjustments = create_guitar_adjustments(guitar_record.guitar_adjustments);
    return Guitar::create(guitar_record.number_of_frets, guitar_record.fret_markers, strings, adjustments);
}

std::shared_ptr<Scale> SGuitarFactory::create_scale(const NoteValue root_note, const ScaleRecord& scale_record) {
    return Scale::create_with_root_note(root_note, scale_record.semitones);
}

std::shared_ptr<Chord> SGuitarFactory::create_chord(const NoteValue root_note, const ChordRecord& chord_record) {
    return Chord::create_with_root_note(root_note, chord_record.intervals);
}

GuitarRecord SGuitarFactory::convertJsonToGuitarRecord(const std::string& json) {
    nlohmann::json j = nlohmann::json::parse(json);
    const auto numberOfFrets = j["NumberOfFrets"].get<int>();
    const auto guitarType = j["GuitarType"].get<std::string>();
    const auto guitarStrings = j["GuitarStrings"].get<std::vector<nlohmann::json>>();
    const auto guitarAdjustments = j["GuitarAdjustments"].get<std::vector<nlohmann::json>>();

    std::cout << "NumberOfFrets: " << numberOfFrets << std::endl;
    std::cout << "GuitarType: " << guitarType << std::endl;

    std::cout << "GuitarStrings" << std::endl;
    std::vector<GuitarStringRecord> guitar_strings_records;

    for (const auto& guitarString : guitarStrings) {
        const auto stringNumber = guitarString["StringNumber"].get<int>();
        const auto startNote = guitarString["StartNote"].get<std::string>();
        std::string startNoteString; // TODO: get start note from StartNote string
        int octave = 0; // TODO: get octave from StartNote string
        std::cout << "StringNumber: " << stringNumber << std::endl;
        std::cout << "StartNote: " << startNote << std::endl;
        guitar_strings_records.emplace_back(0, 0, stringNumber, startNoteString, octave);
    }

    std::cout << "GuitarAdjustments" << std::endl;
    std::vector<GuitarAdjustmentRecord> guitarAdjustmentRecords;

    for (const auto& guitarAdjustment : guitarAdjustments) {
        const auto id = guitarAdjustment["ID"].get<std::string>();
        const auto stringAdjustments = guitarAdjustment["StringAdjustments"].get<std::vector<nlohmann::json>>();

        std::cout << "ID: " << id << std::endl;
        std::cout << "StringAdjustments" << std::endl;
        std::vector<GuitarStringAdjustmentRecord> guitar_string_adjustment_records;

        for (const auto& stringAdjustment : stringAdjustments) {
            const auto stringNumber = stringAdjustment["StringNumber"].get<int>();
            const auto step = stringAdjustment["Step"].get<int>();

            std::cout << "StringNumber: " << stringNumber << std::endl;
            std::cout << "Step: " << step << std::endl;
            guitar_string_adjustment_records.emplace_back(-1, -1, stringNumber, step);
        }
        guitarAdjustmentRecords.emplace_back(-1, -1, id, guitar_string_adjustment_records);
    }

    return {-1, "", numberOfFrets, {}, guitar_strings_records, guitarAdjustmentRecords};
}
