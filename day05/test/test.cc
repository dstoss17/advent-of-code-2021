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

std::string example = "0,9 -> 5,9\n"
                      "8,0 -> 0,8\n"
                      "9,4 -> 3,4\n"
                      "2,2 -> 2,1\n"
                      "7,0 -> 7,4\n"
                      "6,4 -> 2,0\n"
                      "0,9 -> 2,9\n"
                      "3,4 -> 1,4\n"
                      "0,0 -> 8,8\n"
                      "5,5 -> 8,2";

TEST(Day05, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "5");
}

TEST(Day05, ExampleOnePartTwo) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "12");
}

