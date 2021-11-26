//
// Created by dstoss on 8/7/20.
//

#ifndef ADVENT_OF_CODE_2017_UTILS_H
#define ADVENT_OF_CODE_2017_UTILS_H

#include <vector>
#include <iostream>
#include <iterator>
#include <string>

namespace aoc {

template<class T>
std::vector<T> read_in(std::istream &in) {
  std::vector<T> data;
  std::copy(std::istream_iterator<T>(in),
            std::istream_iterator<T>(),
            std::back_inserter(data));
  return data;
}

template<>
std::vector<std::string> read_in(std::istream& in) {
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(in, line)) {
    lines.emplace_back(std::move(line));
  }

  return lines;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& data) {
  std::ostream_iterator<T> out_it(os, "\n");
  std::copy(data.begin(), data.end(), out_it);
  return os;
}

}

#endif //ADVENT_OF_CODE_2017_UTILS_H
