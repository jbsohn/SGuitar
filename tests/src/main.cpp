//
// Created by John Sohn on 11/3/24.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include <cstdlib>
#include <iostream>
#include <string>
#include <doctest/doctest.h>
#include "main.hpp"

std::string Paths::dbPath;
std::string Paths::lapSteelPath;
std::string Paths::pedalSteelPath;

int main(const int argc, char** argv) {
    doctest::Context context;

    if (argc > 2) {
        Paths::dbPath = argv[1];
        Paths::lapSteelPath = argv[2];
        Paths::pedalSteelPath = argv[3];
    } else {
        std::cerr << "Usage: <path-to-db> <path-to-lap-steel> <path-to-pedal-steel>" << std::endl;
        std::exit(0);
    }

    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    if (context.shouldExit()) {
        return res;
    }
    return res;
}
