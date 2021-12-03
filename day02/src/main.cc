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
#include "aoc/point.h"

using Point = aoc::PointT<int>;

enum class Direction {
  kForward,
  kUp,
  kDown
};

struct Command {
  Direction dir;
  int mag;
};

std::istream& operator>>(std::istream& in, Command& command)
{
  char c;
  in >> c;
  if (c == 'f') {
    command.dir = Direction::kForward;
    in.ignore(7);
  }
  else if (c == 'u') {
    command.dir = Direction::kUp;
    in.ignore(2);
  }
  else {
    command.dir = Direction::kDown;
    in.ignore(4);
  }

  in >> command.mag;

  return in;
}

Point execute_commands(const std::vector<Command>& commands)
{
  Point location {0, 0};

  for (auto cmd : commands) {
    switch (cmd.dir) {
    case Direction::kForward:
      location.x += cmd.mag;
      break;

    case Direction::kUp:
      location.y -= cmd.mag;
      break;

    case Direction::kDown:
      location.y += cmd.mag;
      break;

    default:
      break;
    }
  }

  return location;
}

Point execute_commands_steered(const std::vector<Command>& commands)
{
  Point location {0, 0};
  int aim = 0;

  for (auto cmd : commands) {
    switch (cmd.dir) {
    case Direction::kForward:
      location.x += cmd.mag;
      location.y += cmd.mag * aim;
      break;

    case Direction::kUp:
      aim -= cmd.mag;
      break;

    case Direction::kDown:
      aim += cmd.mag;
      break;

    default:
      break;
    }
  }

  return location;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto commands = read_in<Command>(in);
  auto location = execute_commands(commands);
  std::ostringstream out;
  out << location.x * location.y;
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto commands = read_in<Command>(in);
  auto location = execute_commands_steered(commands);
  std::ostringstream out;
  out << location.x * location.y;
  return out.str();
}

} // namespace aoc
