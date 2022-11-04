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
#include <cmath>
#include <algorithm>
#include "aoc/parts.h"
#include "aoc/utils.h"

int ship_power(const std::vector<std::string>& lines)
{
  size_t num_bits = lines[0].size();
  size_t num_lines = lines.size();
  std::vector<int> count(num_bits);
  for (const auto& line : lines) {
    for (size_t ii = 0; ii != num_bits; ii++) {
      count[ii] += line[ii] - '0';
    }
  }

  int gamma = 0;
  int epsilon = 0;
  int cutoff = static_cast<int>(num_lines) / 2;
  for (size_t ii = 0; ii != num_bits; ii++) {
    int ci = count[num_bits - ii - 1];
    if (ci >= cutoff) {
      gamma += std::pow(2, ii);
    }
    else {
      epsilon += std::pow(2, ii);
    }
  }

  return gamma * epsilon;
}

int apply_criteria(const std::vector<std::string>& lines, bool winner)
{
  auto valid = lines;
  size_t ii = 0;
  while (valid.size() > 1) {
    int zero_count = 0;
    int one_count = 0;
    for (size_t jj = 0; jj != valid.size(); jj++) {
      if ('0' == valid[jj][ii]) zero_count++;
      else                      one_count++;
    }

    char remove = '0';
    if ((winner && one_count < zero_count) || (!winner && one_count >= zero_count)) {
      remove = '1';
    }

    auto end = std::remove_if(valid.begin(), valid.end(), [&](const std::string& line) {
      return line[ii] == remove;
    });
    valid.erase(end, valid.end());
    ii++;
  }

  int value = 0;
  std::string result = valid[0];
  int num_bits = static_cast<int>(result.size());
  for (size_t i = 0; i != result.size(); i++) {
    int ci = result[num_bits - i - 1] - '0';
    value += ci * std::pow(2, i);
  }

  return value;
}

int oxygen_rating(const std::vector<std::string>& lines)
{
  return apply_criteria(lines, true);
}

int scrubber_rating(const std::vector<std::string>& lines)
{
  return apply_criteria(lines, false);
}

int life_support_rating(const std::vector<std::string>& lines)
{
  return oxygen_rating(lines) * scrubber_rating(lines);
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto lines = read_in<std::string>(in);
  std::ostringstream out;
  out << ship_power(lines);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto lines = read_in<std::string>(in);
  std::ostringstream out;
  out << life_support_rating(lines);
  return out.str();
}

} // namespace aoc
