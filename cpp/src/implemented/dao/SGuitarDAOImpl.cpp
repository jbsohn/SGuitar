//
// Created by john on 10/12/24.
//

#include "SGuitarDAOImpl.hpp"

std::shared_ptr<SguitarDAO> SguitarDAO::create_sguitar_dao(const std::string &path) {
    return std::make_shared<SGuitarDAOImpl>(path);
}
