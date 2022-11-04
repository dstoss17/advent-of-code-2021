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
#include <numeric>
#include <algorithm>
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

int fuel_cost(int position, int location, bool linear)
{
  int distance = std::abs(position - location);
  if (linear) {
    return distance;
  }
  else {
    return ((distance + 1) * distance) / 2;
  }
}

int compute_fuel_cost(const std::vector<int>& positions, int location, bool linear)
{
  auto cost = [location, linear](int sum, int pos) { return sum + fuel_cost(pos, location, linear); };
  return std::accumulate(positions.begin(), positions.end(), 0, cost);
}

int find_median(std::vector<int> positions)
{
  std::sort(positions.begin(), positions.end());

  size_t size = positions.size();
  if (size % 2 == 0) {
    double median = static_cast<double>(positions[size/2] + positions[size/2 - 1]) / 2.0;
    return static_cast<int>(std::round(median));
  }
  else {
    return positions[size/2];
  }
}

int find_mean(std::vector<int> positions)
{
  double sum = std::accumulate(positions.begin(), positions.end(), 0.0);
  return static_cast<int>(std::round(sum / positions.size()));
}

int find_best_cost(const std::vector<int>& positions, bool linear)
{
  int max_locations = *std::max_element(positions.begin(), positions.end());

  int c1 = compute_fuel_cost(positions, 0, linear);

  for (int location = 1; location < max_locations; location++) {
    int c2 = compute_fuel_cost(positions, location, linear);
    if (c2 > c1) {
      break;
    }

    c1 = c2;
  }

  return c1;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto pos = read_positions(in);
  if (verbose) {
    std::cout << pos;
  }

  std::ostringstream out;
  out << find_best_cost(pos, true);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto pos = read_positions(in);
  if (verbose) {
    std::cout << pos;
  }

  std::ostringstream out;
  out << find_best_cost(pos, false);
  return out.str();
}

} // namespace aoc
