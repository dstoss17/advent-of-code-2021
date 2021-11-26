/*
 * point.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADVENT_OF_CODE_2017_POINT_H
#define ADVENT_OF_CODE_2017_POINT_H

#include <iostream>
#include <tuple>

namespace aoc {

template <typename T>
struct PointT {
  T x, y;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, PointT<T> p) {
  return os << '(' << p.x << ", " << p.y << ')';
}

template <typename T>
inline bool operator==(PointT<T> p1, PointT<T> p2) {
  return (p1.x == p2.x) && (p1.y == p2.y);
}

template <typename T>
inline bool operator!=(PointT<T> p1, PointT<T> p2) {
  return !(p1 == p2);
}

template <typename T>
inline bool operator<(PointT<T> p1, PointT<T> p2) {
  return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
}

template <typename T>
inline bool operator<=(PointT<T> p1, PointT<T> p2) {
  return !(p2 < p1);
}

template <typename T>
inline bool operator>(PointT<T> p1, PointT<T> p2) {
  return (p2 < p1);
}

template <typename T>
inline bool operator>=(PointT<T> p1, PointT<T> p2) {
  return !(p1 < p2);
}

template <typename T>
inline PointT<T> operator+(PointT<T> p1, PointT<T> p2) {
  return {p1.x + p2.x, p1.y + p2.y};
}

template <typename T>
inline PointT<T> operator-(PointT<T> p1, PointT<T> p2) {
  return {p1.x - p2.x, p1.y - p2.y};
}
} // namespace aoc

#endif /* !ADVENT_OF_CODE_2017_POINT_H */
