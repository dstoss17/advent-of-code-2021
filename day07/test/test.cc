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

std::string example = "16,1,2,0,4,2,7,1,2,14";

TEST(Day07, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "2");
}

TEST(Day07, ExampleOnePartTwo) {
  std::string input = "1122";
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "Not implemented");
}

