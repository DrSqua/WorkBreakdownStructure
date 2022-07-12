cmake_minimum_required(VERSION 3.21)
project(WorkBreakdownStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(WorkBreakdownStructure main.cpp Node.cpp WorkBreakdownStructure.h WorkBreakdownStructure.cpp WBSTree.cpp PathAlgorithms.cpp)
