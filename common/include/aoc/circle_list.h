/*
 * circle_list.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADVENT_OF_CODE_2017_CIRCLE_LIST_H
#define ADVENT_OF_CODE_2017_CIRCLE_LIST_H

#include <list>
#include <iostream>
#include <sstream>

namespace aoc {

template<typename T>
class CircleList {
  std::list<T> m_data;
public:
  using iterator = typename std::list<T>::iterator;
  using const_iterator = typename std::list<T>::const_iterator;

  CircleList(T val = T()) : m_data(val) {}
  CircleList(std::initializer_list<T> vals) : m_data(vals) {}

  void rotate(int count) {
    if (count >= 0) rotate_right(count);
    else rotate_left(-count);
  }

  void rotate_right(int count) {
    for (int ii = 0; ii < count; ii++) {
      m_data.splice(m_data.end(), m_data, m_data.begin());
    }
  }

  void rotate_left(int count) {
    for (int ii = 0; ii < count; ii++) {
      auto it = m_data.end();
      it--;
      m_data.splice(m_data.begin(), m_data, it);
    }
  }

  /** @returns the value from the current position and removes it from the list */
  T pop() {
    T val = m_data.back();
    m_data.pop_back();

    return val;
  }

  /** Writes @val at the front of the list */
  void append(const T &val) { m_data.push_back(val); }

  /** @returns the first value in the list */
  const T& front() const noexcept { return m_data.front(); }

  iterator begin() { return m_data.begin(); }
  iterator end() { return m_data.end(); }

  const_iterator begin() const noexcept { return m_data.begin(); }
  const_iterator end() const noexcept { return m_data.end(); }

  const_iterator cbegin() const noexcept { return m_data.cbegin(); }
  const_iterator cend() const noexcept { return m_data.cend(); }

  size_t size() const noexcept { return m_data.size(); }
};

template<typename T>
bool operator==(const CircleList<T> &list1, const CircleList<T> &list2) {
  if (list1.size() != list2.size()) return false;
  return std::equal(list1.cbegin(), list1.cend(), list2.cbegin());
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const CircleList<T>& circle_list) {
  std::ostringstream out;
  for (const auto& val : circle_list) {
    out << val << ' ';
  }

  return os << out.str();
}

} // namespace aoc

#endif /* !CIRCLE_LIST_H */
