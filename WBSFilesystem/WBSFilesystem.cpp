//
// Created by Robbe on 03/08/2022.
//

#include "WBSFilesystem.h"

/*!
 * Takes filename and creates a path object
 * @param filename
 * @return
 */
fs::path getCSVFilepathFromFilename(const std::string &filename) {
    auto filepath = fs::current_path() / "SavedWBSs" / filename;
    filepath.replace_extension("csv");
    return filepath;
}

WorkBreakdownStructure create_wbs(const fs::path& filepath) {
    // Establishing return value
    WorkBreakdownStructure workBreakdownStructure;

    // Create connection
    auto file_string = filepath.string();
    std::ifstream file(file_string);
    if (!file.is_open())
    {
        return{};
    }

    std::string raw_line; // Lijn die wordt gelezen (dus de rij van een csv)
    std::stringstream stringstream;
    std::string segment;

    std::vector<std::string> splitted_line;

    Node node;
    // Processing
    std::getline(file, raw_line); // skip the first line
    while (std::getline(file, raw_line))  // Loop through next lines
    {
        stringstream << raw_line;
        // std::cout << raw_line;

        while(std::getline(stringstream, segment, ',')) {
            splitted_line.push_back(segment);
            char bad_char{'\"'};
            splitted_line.back().erase(std::remove(splitted_line.back().begin(), splitted_line.back().end(), bad_char), splitted_line.back().cend());
        }

        node = Node(splitted_line, workBreakdownStructure);

        // Insert Node
        workBreakdownStructure.insertNode(node);

        // Clear values for next row
        stringstream.clear();
        splitted_line.clear();
    }

    return workBreakdownStructure;
}
