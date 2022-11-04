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
#include <algorithm>
#include "aoc/parts.h"
#include "aoc/utils.h"

using Segment = std::bitset<7>;

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

  in.ignore(2);
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

template <size_t N>
Segment find_by_count(const std::array<Segment, N>& segments, size_t count)
{
  auto it = std::find_if(segments.begin(), segments.end(), [count](Segment s) {
      return s.count() == count;
  });

  if (it == segments.end()) { return Segment(); }
  return *it;
}

const std::array<Segment, 7> kDigitMasks {
// order:  abcdefg
  Segment("0000001"),  // 0
  Segment("0000010"),  // 1
  Segment("0000100"),  // 2
  Segment("0001000"),  // 3
  Segment("0010000"),  // 4
  Segment("0100000"),  // 5
  Segment("1000000"),  // 6
};


std::array<Segment, 10> solve_digits(const Display& display, bool verbose)
{
  std::array<Segment, 10> digits {};
  digits[1] = find_by_count(display.patterns, 2);
  digits[7] = find_by_count(display.patterns, 3);
  digits[4] = find_by_count(display.patterns, 4);
  digits[8] = find_by_count(display.patterns, 7);

  // determine 2 by finding the only bit not set in all patterns
  std::array<int, 7> bit_counts {};
  for (Segment s : display.patterns) {
    for (int idx = 0; idx < 7; idx++) {
      bit_counts[idx] += s[idx] ? 1 : 0;
    }
  }

  auto f_it = std::find(bit_counts.begin(), bit_counts.end(), 9);
  auto f_bit = std::distance(bit_counts.begin(), f_it);
  Segment two_mask(1 << f_bit);
  digits[2] = *std::find_if(display.patterns.begin(), display.patterns.end(), [two_mask](Segment s) {
    return (s & two_mask).none();
  });

  // determine 3 and 5 by finding the other 5 segment patterns and mask them with 2
  // 3 is the one with 6 in the ORd mask, 5 is the one with all set in the mask
  // also determine 0, 6, and 9 by masking with other known digits (1, 2, 4, 7, 8)
  for (size_t idx = 0; idx < 10; idx++) {
    if (display.patterns[idx].count() == 5) {
      Segment ored = display.patterns[idx] | digits[2];
      if (ored.count() == 6) {
        digits[3] = display.patterns[idx];
      }
      else if (ored.all()) {
        digits[5] = display.patterns[idx];
      }
    }

    if (display.patterns[idx].count() == 6) {
      Segment ored_one = display.patterns[idx] | digits[1];
      Segment ored_four = display.patterns[idx] | digits[4];
      if (ored_one != display.patterns[idx]) {
        digits[6] = display.patterns[idx];
      }
      else if (ored_four != display.patterns[idx]) {
        digits[0] = display.patterns[idx];
      }
      else {
        digits[9] = display.patterns[idx];
      }
    }
  }


  if (verbose) {
    for (Segment s : digits) {
      std::cout << s << ' ';
    }
    std::cout << '\n';
  }

  return digits;
}

void solve_digits(const Display& display, std::array<int, 4>* output, bool verbose)
{
  auto digits = solve_digits(display, verbose);

  for (int idx = 0; idx < 4; idx++) {
    Segment digit = display.outputs[idx];
    auto it = std::find(digits.begin(), digits.end(), digit);
    (*output)[idx] = std::distance(digits.begin(), it);
  }
}

int sum_displays(const std::vector<Display>& displays, bool verbose)
{
  int count = 0;

  for (const auto& display : displays) {
    if (verbose) {
      std::cout << display << '\n';
    }

    // solve the 4 output values
    std::array<int, 4> output_digits {};
    solve_digits(display, &output_digits, verbose);

    int num = output_digits[0] * 1000 + output_digits[1] * 100 + output_digits[2] * 10 + output_digits[3];
    count += num;

    if (verbose) {
      std::cout << num << " >> " << count << '\n';
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
  auto displays = read_in<Display>(in);
  if (verbose) {
    std::cout << displays;
  }

  std::ostringstream out;
  out << sum_displays(displays, verbose);
  return out.str();
}

} // namespace aoc
