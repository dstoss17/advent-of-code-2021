/*
 * point.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADVENT_OF_CODE_2020_POINT3D_H
#define ADVENT_OF_CODE_2020_POINT3D_H

#include <iostream>
#include <tuple>

namespace aoc {

template <typename T>
struct Point3DT {
  T x, y, z;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Point3DT<T> p) {
  return os << '(' << p.x << ", " << p.y << ", " << p.z << ')';
}

template <typename T>
inline bool operator==(Point3DT<T> p1, Point3DT<T> p2) {
  return (p1.x == p2.x) && (p1.y == p2.y) && (p1.z == p2.z);
}

template <typename T>
inline bool operator!=(Point3DT<T> p1, Point3DT<T> p2) {
  return !(p1 == p2);
}

template <typename T>
inline bool operator<(Point3DT<T> p1, Point3DT<T> p2) {
  return std::tie(p1.x, p1.y, p1.z) < std::tie(p2.x, p2.y, p2.z);
}

template <typename T>
inline bool operator<=(Point3DT<T> p1, Point3DT<T> p2) {
  return !(p2 < p1);
}

template <typename T>
inline bool operator>(Point3DT<T> p1, Point3DT<T> p2) {
  return (p2 < p1);
}

template <typename T>
inline bool operator>=(Point3DT<T> p1, Point3DT<T> p2) {
  return !(p1 < p2);
}

template <typename T>
inline Point3DT<T> operator+(Point3DT<T> p1, Point3DT<T> p2) {
  return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

template <typename T>
inline Point3DT<T> operator-(Point3DT<T> p1, Point3DT<T> p2) {
  return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}
} // namespace aoc

#endif /* !ADVENT_OF_CODE_2020_POINT3D_H */
