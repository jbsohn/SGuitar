//
// Created by John on 9/29/24.
//

#include <format>
#include <algorithm>
#include "HarmonizedScaleImpl.hpp"
#include "scale.hpp"


HarmonizedScaleImpl::HarmonizedScaleImpl(const NoteValue root_note, const std::vector<int>& semitones) {
    // https://www.bluesguitarinstitute.com/how-to-harmonize-a-scale/
    auto scaleNotes = Scale::create_with_root_note(root_note, semitones)->get_notes();
    std::vector<NoteValue> notes(scaleNotes.size());

    std::ranges::rotate_copy(scaleNotes, scaleNotes.begin() + 0, notes.begin());
    chords.push_back(Chord::create_with_notes(notes));

    std::ranges::rotate_copy(scaleNotes, scaleNotes.begin() + 2, notes.begin());
    chords.push_back(Chord::create_with_notes(notes));

    std::ranges::rotate_copy(scaleNotes, scaleNotes.begin() + 4, notes.begin());
    chords.push_back(Chord::create_with_notes(notes));
}

std::string HarmonizedScaleImpl::test_description() {
    std::string s;

    for (const auto& chord : chords) {
        s += std::format("{}\n", chord->test_description());
    }

    return s;
}

std::shared_ptr<HarmonizedScale> HarmonizedScale::create_harmonized_scale_with_root_note(
    NoteValue root_note, const std::vector<int32_t>& semitones) {
    return std::make_shared<HarmonizedScaleImpl>(root_note, semitones);
}
