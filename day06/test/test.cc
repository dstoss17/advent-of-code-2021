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

TEST(Day06, ExampleOnePartOne) {
  std::string input = "3,4,3,1,2";
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "5934");
}

TEST(Day06, ExampleOnePartTwo) {
  std::string input = "3,4,3,1,2";
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "26984457539");
}

