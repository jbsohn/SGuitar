//
// Created by John on 10/13/24.
//

#ifndef HARMONIZEDSCALEIMPL_HPP
#define HARMONIZEDSCALEIMPL_HPP

#include "chord.hpp"
#include "harmonized_scale.hpp"

class HarmonizedScaleImpl final : public HarmonizedScale {
    std::vector<std::shared_ptr<Chord> > chords = std::vector<std::shared_ptr<Chord> >();

public:
    HarmonizedScaleImpl(NoteValue root_note, const std::vector<int> &semitones);

    std::vector<std::shared_ptr<Chord> > get_chords() override {
        return chords;
    }

    std::string testDescription() override;
};

#endif //HARMONIZEDSCALEIMPL_HPP
