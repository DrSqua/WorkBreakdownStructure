//
// Created by Robbe on 03/08/2022.
//

#ifndef WORKBREAKDOWNSTRUCTURE_WBSFILESYSTEM_H
#define WORKBREAKDOWNSTRUCTURE_WBSFILESYSTEM_H

#include "filesystem"
#include "../WorkBreakdownStructure.h"

#include <vector>
#include <string>

namespace fs = std::filesystem;

fs::path getCSVFilepathFromFilename(const std::string& filename);

[[maybe_unused]] WorkBreakdownStructure create_wbs(const fs::path& filepath);

#endif //WORKBREAKDOWNSTRUCTURE_WBSFILESYSTEM_H
