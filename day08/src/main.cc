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
#include <bitset>
#include <array>
#include "aoc/parts.h"
#include "aoc/utils.h"

using Segment = std::bitset<7>;
const std::array<Segment, 10> numbers {
// order:  abcdefg
  Segment("1110111"),  // 0
  Segment("0010010"),  // 1
  Segment("1011101"),  // 2
  Segment("1011011"),  // 3
  Segment("0111010"),  // 4
  Segment("1101011"),  // 5
  Segment("1101111"),  // 6
  Segment("1010010"),  // 7
  Segment("1111111"),  // 8
  Segment("1111011"),  // 9
};

Segment str_to_segment(const std::string& str)
{
  Segment result; // defaults to all 0

  for (char c : str) {
    // note: order is "reversed" (abcdefg, not gfedcba)
    size_t bit = 'g' - c;
    result.set(bit);
  }

  return result;
}

struct Display {
  std::array<Segment, 10> patterns;
  std::array<Segment, 4> outputs;
};

std::istream& operator>>(std::istream& in, Display& display)
{
  std::string tmp;
  for (auto& pattern : display.patterns) {
    in >> tmp;
    pattern = str_to_segment(tmp);
  }

  in.ignore(3);
  for (auto& output : display.outputs) {
    in >> tmp;
    output = str_to_segment(tmp);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Display& display)
{
  out << "patterns:";
  for (const auto& pattern : display.patterns) {
    out << ' ' << pattern;
  }
  out << " - outputs:";
  for (const auto& output : display.outputs) {
    out << ' ' << output;
  }

  return out;
}

int count_unique(const std::vector<Display>& displays, bool verbose)
{
  // count the number of outputs with 2, 3, 4, or 7 segments enabled
  int count = 0;

  for (const auto& display : displays) {
    if (verbose) {
      std::cout << display << '\n';
    }

    for (auto output : display.outputs) {
      size_t n = output.count();
      if (n == 2 || n == 3 || n == 4 || n == 7) {
        count++;
      }
    }
  }

  return count;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto displays = read_in<Display>(in);
  if (verbose) {
    std::cout << displays;
  }

  std::ostringstream out;
  out << count_unique(displays, verbose);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << "Not implemented";
  return out.str();
}

} // namespace aoc
