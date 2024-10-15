//
// Created by John on 10/13/24.
//

#ifndef GUITARIMPL_H
#define GUITARIMPL_H

#include "guitar.hpp"
#include "guitar_string.hpp"
#include "guitar_adjustment.hpp"

class GuitarImpl final : public Guitar {
    int number_of_frets = 0;
    std::vector<std::shared_ptr<GuitarString> > guitar_strings;
    std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment> > guitar_adjustments;

public:
    GuitarImpl(
        int32_t number_of_frets,
        const std::vector<std::shared_ptr<GuitarString> > &guitar_strings,
        const std::unordered_map<std::string, std::shared_ptr<GuitarAdjustment> > &
        guitar_adjustments);

    void reset_guitar(const std::vector<std::shared_ptr<Note> > &notes, int32_t number_of_frets) override;

    /** strings */
    std::vector</*not-null*/ std::shared_ptr<GuitarString> > get_strings() override;

    void reset_strings() override;

    /** adjustment */
    bool is_adjustment_activated(const std::string &adjustment_id) override;

    void activate_adjustment(const std::string &adjustment_id, bool activated) override;

    void set_adjustment(const std::string &setting_id,
                        const /*not-null*/ std::shared_ptr<GuitarAdjustment> &adjustment) override {
        guitar_adjustments[setting_id] = adjustment;
    }

    /*not-null*/
    std::shared_ptr<GuitarAdjustment> get_adjustment(const std::string &setting_id) override;

    std::string testDescription() override;
};


#endif //GUITARIMPL_H
