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

std::string example = "199\n"
                      "200\n"
                      "208\n"
                      "210\n"
                      "200\n"
                      "207\n"
                      "240\n"
                      "269\n"
                      "260\n"
                      "263";

TEST(Day01, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "7");
}

TEST(Day01, ExampleOnePartTwo) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "5");
}

