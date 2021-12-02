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
#include "aoc/parts.h"
#include "aoc/utils.h"

int count_increase(const std::vector<int>& depth, size_t win_size=1)
{
  int count = 0;
  int val = 0;
  for (size_t ii = 0; ii < win_size; ii++) {
    val += depth[ii];
  }

  for (size_t ii = win_size; ii < depth.size(); ii++) {
    int new_val = val - depth[ii - win_size] + depth[ii];
    if (new_val > val) {
      count++;
    }

    val = new_val;
  }

  return count;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto depth = read_in<int>(in);
  std::ostringstream out;
  out << count_increase(depth);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto depth = read_in<int>(in);
  std::ostringstream out;
  out << count_increase(depth, 3);
  return out.str();
}

} // namespace aoc
