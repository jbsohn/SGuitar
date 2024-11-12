//
// Created by John on 11/3/24.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include <cstdlib>
#include <filesystem>
#include <doctest/doctest.h>
#include "Tests.hpp"

std::string Paths::dbPath;

#include <iostream>
#include <string>

int main(const int argc, char** argv) {
    doctest::Context context;

    // read argument of DB from argument
    if (argc > 1) {
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
