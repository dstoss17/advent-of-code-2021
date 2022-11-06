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

std::string example = "[({(<(())[]>[[{[]{<()<>>\n"
                      "[(()[<>])]({[<{<<[]>>(\n"
                      "{([(<{}[<>[]}>{[]{[(<()>\n"
                      "(((({<>}<{<{<>}{[]{[]{}\n"
                      "[[<[([]))<([[{}[[()]]]\n"
                      "[{[{({}]{}}([{[{{{}}([]\n"
                      "{<[[]]>}<{[{[{[]{()[[[]\n"
                      "[<(<(<(<{}))><([]([]()\n"
                      "<{([([[(<>()){}]>(<<{{\n"
                      "<{([{{}}[<[[[<>{}]]]>[]]";

TEST(Day10, ExampleOnePartOne) {
  std::string input = example;
  std::istringstream in(input);
  EXPECT_EQ(aoc::part1(in, kVerbose), "26397");
}

TEST(Day10, ExampleOnePartTwo) {
  std::string input = "1122";
  std::istringstream in(input);
  EXPECT_EQ(aoc::part2(in, kVerbose), "Not implemented");
}

TEST(Day10, ExampleValidLine) {
  std::string input = "[{}]";
  EXPECT_EQ(first_invalid(input), ' ');
}

TEST(Day10, ExampleInvalidLine) {
  std::string input = "{([(<{}[<>[]}>{[]{[(<()>";
  EXPECT_EQ(first_invalid(input), '}');
}
