/*
 * point.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADVENT_OF_CODE_2020_POINT4D_H
#define ADVENT_OF_CODE_2020_POINT4D_H

#include <iostream>
#include <tuple>

namespace aoc {

template <typename T>
struct Point4DT {
  T x, y, z, w;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Point4DT<T> p) {
  return os << '(' << p.x << ", " << p.y << ", " << p.z << ", " << p.w << ')';
}

template <typename T>
inline bool operator==(Point4DT<T> p1, Point4DT<T> p2) {
  return (p1.x == p2.x) && (p1.y == p2.y) && (p1.z == p2.z) && (p1.w == p2.w);
}

template <typename T>
inline bool operator!=(Point4DT<T> p1, Point4DT<T> p2) {
  return !(p1 == p2);
}

template <typename T>
inline bool operator<(Point4DT<T> p1, Point4DT<T> p2) {
  return std::tie(p1.x, p1.y, p1.z, p1.w) < std::tie(p2.x, p2.y, p2.z, p2.w);
}

template <typename T>
inline bool operator<=(Point4DT<T> p1, Point4DT<T> p2) {
  return !(p2 < p1);
}

template <typename T>
inline bool operator>(Point4DT<T> p1, Point4DT<T> p2) {
  return (p2 < p1);
}

template <typename T>
inline bool operator>=(Point4DT<T> p1, Point4DT<T> p2) {
  return !(p1 < p2);
}

template <typename T>
inline Point4DT<T> operator+(Point4DT<T> p1, Point4DT<T> p2) {
  return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z, p1.w + p2.w};
}

template <typename T>
inline Point4DT<T> operator-(Point4DT<T> p1, Point4DT<T> p2) {
  return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z, p1.w + p2.w};
}
} // namespace aoc

#endif /* !ADVENT_OF_CODE_2020_POINT4D_H */
