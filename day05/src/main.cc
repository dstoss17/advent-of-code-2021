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
#include <map>
#include "aoc/parts.h"
#include "aoc/utils.h"
#include "aoc/point.h"
#include "aoc/image.h"

using Point = aoc::PointT<int>;
struct Vent {
  Point p1, p2;
};

std::istream& operator>>(std::istream& in, Vent& vent)
{
  in >> vent.p1.x;
  in.ignore(1);
  in >> vent.p1.y;

  in.ignore(4);

  in >> vent.p2.x;
  in.ignore(1);
  in >> vent.p2.y;
  return in;
}

void draw_line(const Vent& vent, bool diagonal, std::map<Point, int>* points)
{
  if (vent.p1.x == vent.p2.x) {
    int y1 = std::min(vent.p1.y, vent.p2.y);
    int y2 = std::max(vent.p1.y, vent.p2.y);
    int x = vent.p1.x;
    for (int y = y1; y <= y2; y++) {
      Point p {x, y};
      (*points)[p]++;
    }
  }

  if (vent.p1.y == vent.p2.y) {
    int x1 = std::min(vent.p1.x, vent.p2.x);
    int x2 = std::max(vent.p1.x, vent.p2.x);
    int y = vent.p1.y;
    for (int x = x1; x <= x2; x++) {
      Point p {x, y};
      (*points)[p]++;
    }
  }

  if (diagonal && vent.p1.x != vent.p2.x && vent.p1.y != vent.p2.y) {
    int x_off = (vent.p1.x > vent.p2.x) ? -1 : 1;
    int y_off = (vent.p1.y > vent.p2.y) ? -1 : 1;
    int x = vent.p1.x;
    int y = vent.p1.y;
    int count = std::abs(vent.p1.x - vent.p2.x) + 1;
    for (int ii = 0; ii < count; ii++) {
      Point p {x + x_off * ii, y + y_off * ii};
      (*points)[p]++;
    }
  }
}

size_t count_overlap(const std::vector<Vent>& vents, bool diagonal=false)
{
  std::map<Point, int> points;
  for (const auto& vent : vents) {
    draw_line(vent, diagonal, &points);
  }

  return std::count_if(points.begin(), points.end(), [](const auto& item) {
    return item.second >= 2;
  });
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto vents = read_in<Vent>(in);
  std::ostringstream out;
  out << count_overlap(vents);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto vents = read_in<Vent>(in);
  std::ostringstream out;
  out << count_overlap(vents, true);
  return out.str();
}

} // namespace aoc
