//
// Created by John on 11/4/24.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <doctest/doctest.h>
#include "guitar_record.hpp"
#include "SGuitar_factory.hpp"

std::string read_file(const std::string& file_name) {
    if (std::filesystem::exists(file_name)) {
        std::ifstream file(file_name);
        std::string content((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
        return content;
    }
    std::cerr << "File not found: " << file_name << std::endl;
    return "";
}

TEST_CASE("Testing import") {
    const auto jsonString = read_file("../import/Pedal Steel/Buddy E9");
    const auto guitar = SGuitarFactory::convertJsonToGuitarRecord(jsonString);
    std::cout << "TEST" << std::endl;
}
