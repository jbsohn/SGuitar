//
// Created by John Sohn on 11/17/24.
//

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "Utility.hpp"

std::string read_file(const std::string& file_name) {
    if (std::filesystem::exists(file_name)) {
        std::ifstream file(file_name);
        std::string content((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
        return content;
    }
    std::cerr << "File not found: " << file_name << std::endl;
    return "";
}
