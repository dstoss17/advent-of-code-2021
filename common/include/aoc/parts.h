/*
 * aoc_parts.h
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef AOC_PARTS_H
#define AOC_PARTS_H

#include <string>
#include <iostream>

namespace aoc {

/**
 * Executes part 1 of the problem.
 * @param [in] filename name of input data file
 * @param [in] verbose enable verbose printing
 * @returns the answer for part 1
 */
std::string part1(std::istream& in, bool verbose=false);

/**
 * Executes part 2 of the problem.
 * @param [in] filename name of input data file
 * @param [in] verbose enable verbose printing
 * @returns the answer for part 2
 */
std::string part2(std::istream& in, bool verbose=false);

} // namespace aoc

#endif /* !AOC_PARTS_H */
