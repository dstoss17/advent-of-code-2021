/*
 * main.cc
 * Copyright (C) 2021 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#include "impl.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
#include "aoc/parts.h"
#include "aoc/utils.h"

bool is_closing_token(char c)
{
  return c == '>' || c == '}' || c == ']' || c == ')';
}

bool matching_token(char c1, char c2)
{
  switch (c1) {
  case '(': return c2 == ')';
  case '[': return c2 == ']';
  case '{': return c2 == '}';
  case '<': return c2 == '>';
  default: return false;
  }
}

uint64_t char_score(char c) {
  switch (c) {
  case ')': return 3;
  case ']': return 57;
  case '}': return 1197;
  case '>': return 25137;
  default: return 0;
  }
}

char first_invalid(std::string_view line)
{
  std::stack<char> tokens;
  for (auto c : line) {
    if (is_closing_token(c)) {
      if (tokens.empty()) { return c; }
      if (!matching_token(tokens.top(), c)) {
        return c;
      }

      tokens.pop();
    }
    else {
      tokens.push(c);
    }
  }

  return ' ';
}

uint64_t compute_score(std::istream& in, bool verbose)
{
  uint64_t score = 0;
  std::string line;

  while (std::getline(in, line)) {
    // compute score for the line and add to the total
    if (verbose) {
      std::cout << line << '\n';
    }

    score += char_score(first_invalid(line));
  }

  return score;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << compute_score(in, verbose);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << "Not implemented";
  return out.str();
}

} // namespace aoc
