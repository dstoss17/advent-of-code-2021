/*
 * double_buffer.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef DOUBLE_BUFFER_H
#define DOUBLE_BUFFER_H

#include <array>

namespace aoc {

template <typename T>
class DoubleBuffer {
public:
  const T& current() const noexcept { return buffer_[idx_]; }
  T& current() noexcept { return buffer_[idx_]; }

  const T& next() const noexcept { return buffer_[1 - idx_]; }
  T& next() noexcept { return buffer_[1 - idx_]; }

  void advance() { idx_ = 1 - idx_; }
private:
  int idx_ = 0;
  std::array<T, 2> buffer_;
};

} // namespace aoc

#endif /* !DOUBLE_BUFFER_H */
