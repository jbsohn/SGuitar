//
// Created by john on 10/12/24.
//

#ifndef SGUITARDBIMPL_H
#define SGUITARDBIMPL_H

#include <SQLiteCpp/SQLiteCpp.h>
#include "sguitar_DAO.hpp"

class SGuitarDAOImpl final : public SguitarDAO {
    SQLite::Database database;

public:
    explicit SGuitarDAOImpl(const std::string &path): database(path, SQLite::OPEN_READWRITE) {
    }

    SQLite::Database &getDatabase() { return database; }
};

#endif //SGUITARDBIMPL_H
