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

int main(const int argc, char** argv) {
    doctest::Context context;

    if (argc > 1) {
        // path to DB
        Paths::dbPath = argv[1];
    } else {
        std::cerr << "Usage: <path-to-db>" << std::endl;
        std::exit(0);
    }

    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    if (context.shouldExit()) {
        return res;
    }
    return res;
}
