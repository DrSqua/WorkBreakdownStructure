cmake_minimum_required(VERSION 3.21)
project(WorkBreakdownStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(WorkBreakdownStructure main.cpp Node.cpp WorkBreakdownStructure.h WorkBreakdownStructure.cpp WBSTree.cpp PathAlgorithms.cpp Rendering/Rendering.h Rendering/FreeDisplayNode.cpp Rendering/DisplayNode.cpp Rendering/StaticDisplayNode.cpp Rendering/WbsDisplayClass.cpp)
