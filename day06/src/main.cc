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
#include <cstdint>
#include <numeric>
#include "aoc/parts.h"
#include "aoc/utils.h"

std::vector<int> read_fish(std::istream& in)
{
  std::vector<int> fish;
  int tmp;
  while (in >> tmp) {
    fish.push_back(tmp);
    in.ignore(1);
  }

  return fish;
}

void display(const std::vector<uint64_t>& days)
{
  std::cout << "state:";
  for (auto d : days) {
    std::cout << ' ' << d;
  }
  std::cout << '\n';
}

void simulate_day(std::vector<uint64_t>::iterator begin, std::vector<uint64_t>::iterator end)
{
  uint64_t count = *begin;
  if (count == 0 || begin + 9 >= end) {
    return; // no fish to simulate
  }

  auto day = begin + 9;
  while (day < end) {
    *day += count;
    day += 7;
  }
}

uint64_t simulate(const std::vector<int>& initial_fish, int num_days, bool verbose)
{
  std::vector<uint64_t> days(num_days + 9);

  // initialize fish
  for (int f : initial_fish) {
    days[f] += 1;
  }
  
  if (verbose) {
    display(days);
  }

  // simulate each day til the end of the vector
  for (auto d = days.begin(), e = days.end(); d != e; d++) {
    simulate_day(d, e);
  }
  
  if (verbose) {
    display(days);
  }

  // sum the number of fish
  return std::accumulate(days.begin(), days.end(), uint64_t{0});
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto fish = read_fish(in);
  auto final_fish = simulate(fish, 80, verbose);

  std::ostringstream out;
  out << final_fish;
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto fish = read_fish(in);
  auto final_fish = simulate(fish, 256, verbose);

  std::ostringstream out;
  out << final_fish;
  return out.str();
}

} // namespace aoc
