//
// Created by john on 10/12/24.
//

#ifndef SGUITARDBIMPL_H
#define SGUITARDBIMPL_H

class SGuitarDBImpl final : public SguitarDB {
    SQLite::Database database;
public:
    explicit SGuitarDBImpl(const std::string& path): database(path) { }
    SQLite::Database& getDatabase() { return database; }
};

#endif //SGUITARDBIMPL_H
