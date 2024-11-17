//
// Created by John Sohn on 11/3/24.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <doctest/doctest.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <fmt/format.h>
#include "main.hpp"

std::string Paths::ddlPath;
std::string Paths::dbPath;
std::string Paths::lapSteelPath;
std::string Paths::pedalSteelPath;

// imported from SGuitar
std::string read_file(const std::string& file_name);

void setup() {
    const std::string dbPath = Paths::dbPath;
    std::filesystem::remove(dbPath);
    SQLite::Database db(dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    const std::string ddl = read_file(Paths::ddlPath);
    db.exec(ddl);
}

void teardown() {
    std::filesystem::remove(Paths::dbPath);
}

std::string testDBPath() {
    std::string path = std::filesystem::temp_directory_path();
    std::string templateName = fmt::format("{}/SGXXXXXX", path);
    const int id = mkstemp(templateName.data());
    if (id < 0) {
        throw std::runtime_error("Failed to create temporary directory");
    }
    close(id);
    return templateName;
}

void readArguments(const int argc, char** argv) {
    if (argc > 2) {
        Paths::ddlPath = argv[1];
        Paths::lapSteelPath = argv[2];
        Paths::pedalSteelPath = argv[3];
        Paths::dbPath = testDBPath();
    } else {
        std::cerr << "Usage: <path-to-ddl> <path-to-lap-steel> <path-to-pedal-steel>" << std::endl;
        std::exit(0);
    }
}

int main(const int argc, char** argv) {
    readArguments(argc, argv);
    setup();
    std::atexit(&teardown);

    doctest::Context context;
    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    if (context.shouldExit()) {
        return res;
    }
    return res;
}
