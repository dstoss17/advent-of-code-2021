/*
 * image.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef ADVENT_OF_CODE_2017_IMAGE_H
#define ADVENT_OF_CODE_2017_IMAGE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace aoc {

/** An image */
template<typename T>
class ImageT {
public:
  explicit ImageT(size_t width = 1, size_t height = 1, const T& val = T()) :
      m_data(width * height, val),
      m_width(width) {}

  ~ImageT() = default;
  ImageT(const ImageT&) = default;
  ImageT(ImageT&&) noexcept = default;
  ImageT& operator=(const ImageT&) = default;
  ImageT& operator=(ImageT&&) noexcept = default;

  const T& operator()(size_t x, size_t y) const noexcept {
    return m_data[x + y * width()];
  }

  T& operator()(size_t x, size_t y) noexcept {
    return m_data[x + y * width()];
  }

  const T& at(size_t x, size_t y) const {
    return m_data.at(x + y * width());
  }

  T& at(size_t x, size_t y) {
    return m_data.at(x + y * width());
  }

  size_t width() const noexcept {
    return m_width;
  }

  size_t height() const noexcept {
    return m_data.size() / width();
  }

  void reshape(size_t width, size_t height) {
    m_width = width;
    m_data.resize(width * height);
  }

  using iterator = typename std::vector<T>::iterator;

  iterator begin() {
    return m_data.begin();
  }

  iterator end() {
    return m_data.end();
  }

  using const_iterator = typename std::vector<T>::const_iterator;

  const_iterator begin() const {
    return m_data.begin();
  }

  const_iterator end() const {
    return m_data.end();
  }

private:
  std::vector<T> m_data;
  size_t m_width;
};

template <typename T>
inline bool operator==(const ImageT<T>& im1, const ImageT<T>& im2) {
  if (im1.width() != im2.width() || im1.height() != im2.height()) {
    return false;
  }

  return std::equal(im1.begin(), im1.end(), im2.begin());
}

template <typename T>
inline bool operator!=(const ImageT<T>& im1, const ImageT<T>& im2) {
  return !(im1 == im2);
}

template <typename T>
inline bool operator<(const ImageT<T>& im1, const ImageT<T>& im2) {
  if (im1.width() != im2.width()){
    return im1.width() < im2.width();
  }
  if (im1.height() != im2.height()) {
    return im1.height() < im2.height();
  }

  for (auto it1 = im1.begin(), it2 = im2.begin(), end = im1.end();
       it1 != end; ++it1, ++it2) {
    if (*it1 < *it2) {
      return true;
    }
    else if (*it1 > *it2) {
      return false;
    }
  }
  return false;
}

template <typename T>
inline bool operator>(const ImageT<T>& im1, const ImageT<T>& im2) {
  return im2 < im1;
}

template <typename T>
inline bool operator>=(const ImageT<T>& im1, const ImageT<T>& im2) {
  return !(im2 > im1);
}

template <typename T>
inline bool operator<=(const ImageT<T>& im1, const ImageT<T>& im2) {
  return !(im1 > im2);
}

/** Prints an image to the output stream */
template <typename T>
std::ostream& operator<<(std::ostream& os, const ImageT<T>& image) {
  std::ostringstream out;
  for (size_t h = 0; h != image.height(); h++) {
    if (h > 0) out << '\n';
    for (size_t w = 0; w != image.width(); w++) {
      out << image.at(w, h);
    }
  }

  return os << out.str();
}

} // namespace aoc

#endif /* !ADVENT_OF_CODE_2017_IMAGE_H */
