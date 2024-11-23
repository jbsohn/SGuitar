//
// Created by John Sohn on 11/7/24.
//

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>
#include <nlohmann/json.hpp>
#include "guitar_DAO.hpp"
#include "guitar_record.hpp"
#include "guitar_import.hpp"
#include "Utility.hpp"

std::tuple<std::string, int> getNoteAndOctave(const std::string& noteOctave) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(noteOctave);

    while (std::getline(tokenStream, token, '-')) {
        tokens.push_back(token);
    }

    try {
        auto note = tokens.at(0);
        note = std::regex_replace(note, std::regex("#"), "♯");

        auto octave = std::stoi(tokens.at(1));
        return std::make_tuple(note, octave);
    } catch (const std::out_of_range& e) {
        std::cerr << e.what() << std::endl;
    }
    return std::make_tuple("", -1);
}

int guitarTypeFromPath(const std::string& path) {
    std::string searchPath = path;
#ifdef _WIN32
    std::ranges::replace(searchPath, '\\', '/');
#endif

    if (searchPath.find("/Pedal Steel/") != std::string::npos) {
        return 1;
    }
    if (searchPath.find("/Lap Steel/") != std::string::npos) {
        return 2;
    }
    return -1;
}

std::string guitarNameFromPath(const std::string& path) {
    std::string editPath = path;
    const std::string pedalSteel = "/Pedal Steel/";
    if (const auto i = editPath.find(pedalSteel); i != std::string::npos) {
        editPath.erase(0, i + pedalSteel.length());
    }

    const std::string lapSteel = "/Lap Steel/";
    if (const auto i = editPath.find(lapSteel); i != std::string::npos) {
        editPath.erase(0, i + lapSteel.length());
    }
    return editPath;
}

bool GuitarImport::importJsonGuitarFromPath(const std::string& fromPath,
                                            const std::shared_ptr<GuitarDAO>& toGuitarDAO
    ) {
    for (const auto& entry : std::filesystem::directory_iterator(fromPath)) {
        std::string json = read_file(entry.path().string());
        auto guitarRecord = convertJsonToGuitarRecord(entry.path().string(), json);
        toGuitarDAO->add_guitar(guitarRecord);
    }
    return true;
}

GuitarRecord GuitarImport::convertJsonToGuitarRecord(const std::string& filename, const std::string& json) {
    nlohmann::json j = nlohmann::json::parse(json);
    const auto numberOfFrets = j["NumberOfFrets"].get<int>();
    const auto guitarType = j["GuitarType"].get<std::string>();
    const auto guitarStrings = j["GuitarStrings"].get<std::vector<nlohmann::json>>();
    const auto guitarAdjustments = j.contains("GuitarAdjustments")
                                       ? j["GuitarAdjustments"].get<std::vector<nlohmann::json>>()
                                       : std::vector<nlohmann::json>();
    const auto name = guitarNameFromPath(filename);
    const auto type = guitarTypeFromPath(filename);

    std::vector<GuitarStringRecord> guitarStringRecords;
    for (const auto& guitarString : guitarStrings) {
        const auto stringNumber = guitarString["StringNumber"].get<int>();
        const auto startNote = guitarString["StartNote"].get<std::string>();

        auto noteOctave = getNoteAndOctave(startNote);
        guitarStringRecords.emplace_back(0, 0, stringNumber, std::get<0>(noteOctave), std::get<1>(noteOctave));
    }

    std::vector<GuitarAdjustmentRecord> guitarAdjustmentRecords;
    for (const auto& guitarAdjustment : guitarAdjustments) {
        const auto id = guitarAdjustment["ID"].get<std::string>();
        const auto stringAdjustments = guitarAdjustment["StringAdjustments"].get<std::vector<nlohmann::json>>();
        std::vector<GuitarStringAdjustmentRecord> guitar_string_adjustment_records;

        for (const auto& stringAdjustment : stringAdjustments) {
            const auto stringNumber = stringAdjustment["StringNumber"].get<int>();
            const auto step = stringAdjustment["Step"].get<int>();
            guitar_string_adjustment_records.emplace_back(std::nullopt, -1, stringNumber, step);
        }
        guitarAdjustmentRecords.emplace_back(std::nullopt, -1, id, 0, 0, guitar_string_adjustment_records);
    }
    return {std::nullopt, name, numberOfFrets, {}, type, guitarStringRecords, guitarAdjustmentRecords};
}
