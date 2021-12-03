/*
 * test.cc
 * Copyright (C) 2021 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#include "gtest/gtest.h"
#include "aoc/parts.h"
#include "impl.h"
#include <sstream>
#include <string>

// Enable verbose prints if compiled in debug mode (i.e. NDEBUG is NOT defined)
#ifndef NDEBUG
constexpr bool kVerbose = true;
#else
constexpr bool kVerbose = false;
#endif

std::string example = "00100\n"
                      "11110\n"
                      "10110\n"
                      "10111\n"
                      "10101\n"
                      "01111\n"
                      "00111\n"
                      "11100\n"
                      "10000\n"
                      "11001\n"
                      "00010\n"
                      "01010";

TEST(Day03, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "198");
}

TEST(Day03, ExampleOnePartTwo) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "230");
}

