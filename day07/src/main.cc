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
#include "aoc/parts.h"
#include "aoc/utils.h"

std::vector<int> read_positions(std::istream& in)
{
  std::vector<int> positions;
  int tmp;
  while (in >> tmp) {
    positions.push_back(tmp);
    in.ignore(1);
  }

  return positions;
}

int find_min_position(std::vector<int> positions)
{
  int min_pos = -1;
  int min_sum = std::numeric_limits<int>::max();
  int max_val = *std::max_element(positions.begin(), positions.end());
  for (int ii = 0; ii <= max_val; ii++) {
    // accumulate magnitude
    int sum = 0;
    for (int pos : positions) {
      sum += std::abs(pos);
    }

    if (sum < min_sum) {
      min_sum = sum;
      min_pos = ii;
    }

    // subtract 1 from each position
    for (int& pos : positions) {
      --pos;
    }
  }

  return min_pos;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto pos = read_positions(in);
  if (verbose) {
    std::cout << pos;
  }

  std::ostringstream out;
  out << find_min_position(pos);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << "Not implemented";
  return out.str();
}

} // namespace aoc
