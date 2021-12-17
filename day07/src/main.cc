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

int compute_fuel_cost(int pos, const std::vector<int>& positions, bool part2)
{
  int total_cost = 0;
  for (int p : positions) {
    int distance = std::abs(pos - p);
    int cost = (part2) ? ((distance + 1) * distance) / 2 : distance;

    total_cost += cost;
  }

  return total_cost;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto pos = read_positions(in);
  if (verbose) {
    std::cout << pos;
  }

  int min_pos = find_median(pos);
  std::ostringstream out;
  out << compute_fuel_cost(min_pos, pos, false);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto pos = read_positions(in);
  if (verbose) {
    std::cout << pos;
  }

  int min_pos = find_mean(pos);
  std::ostringstream out;
  out << compute_fuel_cost(min_pos, pos, true);
  return out.str();
}

} // namespace aoc
