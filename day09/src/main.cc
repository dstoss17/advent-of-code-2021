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
#include <vector>
#include <unordered_set>
#include <array>
#include "aoc/parts.h"
#include "aoc/utils.h"
#include "aoc/image.h"
#include "aoc/point.h"

using Map = aoc::ImageT<char>;
Map read_map(std::istream& in)
{
  auto lines = aoc::read_in<std::string>(in);

  size_t yy = lines.size();
  size_t xx = lines[0].size();

  Map map(xx + 2, yy + 2, '9');
  for (size_t y = 0; y != yy; y++) {
    const std::string& line = lines[y];
    for (size_t x = 0; x != xx; x++) {
      map(x+1, y+1) = line[x];
    }
  }

  return map;
}

int risk_level(const Map& map, bool verbose)
{
  size_t w = map.width();
  size_t h = map.height();

  int risk = 0;
  for (size_t y = 1; y + 1 != h; y++) {
    for (size_t x = 1; x + 1 != w; x++) {
      char c = map(x, y);
      if (c < map(x+1, y) && c < map(x-1, y) && c < map(x, y+1) && c < map(x, y-1)) {
        risk += (c - '0') + 1;
        if (verbose) {
          std::cout << c << ": (" << x << ", " << y << ")\n";
        }
      }
    }
  }

  return risk;
}

using Coordinate = aoc::PointT<size_t>;
template <>
struct std::hash<Coordinate> {
  std::size_t operator()(const Coordinate& c) const noexcept {
    std::size_t h1 = std::hash<size_t>{}(c.x);
    std::size_t h2 = std::hash<size_t>{}(c.y);
    return h1 ^ (h2 << 1);
  }
};

void add_neighbors(
  const Map& map,
  Coordinate start,
  std::vector<Coordinate>* out_basin,
  std::unordered_set<Coordinate>* out_seen)
{
  std::vector<Coordinate>& basin = *out_basin;
  std::unordered_set<Coordinate>& seen = *out_seen;

  std::array<Coordinate, 4> neighbors {
    Coordinate { start.x, start.y - 1 },
    Coordinate { start.x, start.y + 1 },
    Coordinate { start.x + 1, start.y },
    Coordinate { start.x - 1, start.y },
  };

  for (Coordinate c : neighbors) {
    if (seen.contains(c)) {
      continue;
    }

    if (map(c.x, c.y) != '9') {
      basin.push_back(c);
      seen.insert(c);
      add_neighbors(map, c, &basin, &seen);
    }
  }
}

int64_t basin_sizes(const Map& map, bool verbose)
{
  std::unordered_set<Coordinate> seen;
  std::vector<std::vector<Coordinate>> basins;

  size_t w = map.width();
  size_t h = map.height();

  for (size_t y = 1; y + 1 != h; y++) {
    for (size_t x = 1; x + 1 != w; x++) {
      Coordinate c {x, y};
      if (seen.contains(c)) {
        continue;
      }

      // if this point is not a peak ('9'), then start a new basin record
      if (map(x, y) == '9') {
        continue;
      }
      basins.resize(basins.size() + 1);
      basins.back().push_back(c);
      seen.insert(c);

      // add all of the points in the basin
      add_neighbors(map, c, &basins.back(), &seen);
    }
  }

  if (basins.size() < 3) {
    throw std::runtime_error("Not enough basins found");
  }

  // find the three largest basin sizes
  std::sort(basins.begin(), basins.end(), [](const std::vector<Coordinate>&a, const std::vector<Coordinate>& b) {
      return a.size() > b.size();
      });

  return basins[0].size() * basins[1].size() * basins[2].size();
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto map = read_map(in);
  if (verbose) {
    std::cout << map << '\n';
  }

  std::ostringstream out;
  out << risk_level(map, verbose);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto map = read_map(in);
  if (verbose) {
    std::cout << map << '\n';
  }

  std::ostringstream out;
  out << basin_sizes(map, verbose);
  return out.str();
}

} // namespace aoc
