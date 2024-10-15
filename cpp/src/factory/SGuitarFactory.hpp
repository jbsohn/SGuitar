//
// Created by John on 10/14/24.
//

#ifndef GUITARFACTORY_H
#define GUITARFACTORY_H

#include "guitar.hpp"
#include "guitar_record.hpp"
#include "scale_record.hpp"
#include "chord_record.hpp"

class SGuitarFactory {
public:
    static std::shared_ptr<Guitar> createGuitar(const GuitarRecord &guitar_record);

    static std::shared_ptr<Guitar> createScale(const ScaleRecord &scale_record);

    static std::shared_ptr<Guitar> createChord(const ChordRecord &chord_record);
};

#endif //GUITARFACTORY_H
