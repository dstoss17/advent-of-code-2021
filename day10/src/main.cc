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
#include <vector>
#include <algorithm>
#include "aoc/parts.h"
#include "aoc/utils.h"

static bool is_closing_token(char c)
{
  return c == '>' || c == '}' || c == ']' || c == ')';
}

static bool matching_token(char c1, char c2)
{
  switch (c1) {
  case '(': return c2 == ')';
  case '[': return c2 == ']';
  case '{': return c2 == '}';
  case '<': return c2 == '>';
  default: return false;
  }
}

static uint64_t char_score(char c) {
  switch (c) {
  case ')': return 3;
  case ']': return 57;
  case '}': return 1197;
  case '>': return 25137;
  default: return 0;
  }
}

static uint64_t token_score(char c) {
  switch (c) {
  case '(': return 1;
  case '[': return 2;
  case '{': return 3;
  case '<': return 4;
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

uint64_t score_incomplete_line(std::string_view line)
{
  std::stack<char> tokens;

  for (auto c : line) {
    if (is_closing_token(c)) {
      if (tokens.empty()) { return c; }
      if (!matching_token(tokens.top(), c)) {
        // invalid line: discard it
        return 0;
      }

      tokens.pop();
    }
    else {
      tokens.push(c);
    }
  }

  // score the data on the stack
  uint64_t score = 0;
  while (!tokens.empty()) {
    char c = tokens.top();
    tokens.pop();

    if (!is_closing_token(c)) {
      score *= 5;
      score += token_score(c);
    }
  }

  return score;
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

uint64_t compute_completion_score(std::istream& in)
{
  std::string line;
  std::vector<uint64_t> line_score;

  while (std::getline(in, line)) {
    // compute score for the line and add to the total
    uint64_t score = score_incomplete_line(line);
    if (score > 0) {
      line_score.push_back(score);
    }
  }

  size_t median_offset = line_score.size() / 2;
  auto median = line_score.begin() + median_offset;
  std::nth_element(line_score.begin(), median, line_score.end());

  return line_score[median_offset];
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << compute_score(in, verbose);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << compute_completion_score(in);
  return out.str();
}

} // namespace aoc
