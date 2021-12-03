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

std::string example = "forward 5\n"
                      "down 5\n"
                      "forward 8\n"
                      "up 3\n"
                      "down 8\n"
                      "forward 2";

TEST(Day02, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "150");
}

TEST(Day02, ExampleOnePartTwo) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "900");
}

