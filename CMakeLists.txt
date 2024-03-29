cmake_minimum_required(VERSION 3.17)

project(Advent-of-Code-2021
  VERSION 1.0
  DESCRIPTION "Advent of Code 2021 (C++)"
  LANGUAGES CXX)

# C++ version flags and compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

# Option to force color output
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)

if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
       add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

# Add cmake common functions
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# IDE folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable testing
enable_testing()
include(AddGoogleTest)

# Boilerplate and project files
include(CommonFunctions)
add_subdirectory(common)
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day13)
add_subdirectory(day14)
add_subdirectory(day15)
add_subdirectory(day16)
add_subdirectory(day17)
add_subdirectory(day18)
add_subdirectory(day19)
add_subdirectory(day20)
add_subdirectory(day21)
add_subdirectory(day22)
add_subdirectory(day23)
add_subdirectory(day24)
add_subdirectory(day25)
