//
// Created by John on 11/3/24.
//

#define DOCTEST_CONFIG_IMPLEMENT
#include <filesystem>
#include <doctest/doctest.h>

void setup_test_db() {
    // auto test = std::filesystem::current_path();
    //
    // std::filesystem::remove_all("./db");
    // std::filesystem::create_directory("./db");
    // std::filesystem::copy_file("../db/main.sqlite3", "./db/test.sqlite3");
}

void teardown_test_db() {
    // std::filesystem::remove_all("./db");
}

int main(const int argc, char** argv) {
    doctest::Context context;
    setup_test_db();

    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    if (context.shouldExit()) {
        return res;
    }

    teardown_test_db();
    return res;
}

