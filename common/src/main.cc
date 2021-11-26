/*
 * main.cc
 * Copyright (C) 2020 dstoss <dstoss17@vt.edu>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <chrono>
#include <stdexcept>

#include "aoc/parts.h"

/** Process arguments */
enum Args {
  PROCESS_NAME,
  FILENAME,
  NUM_REQUIRED,

  // optional arguments
  VERBOSE = NUM_REQUIRED,
  TIME_EXECUTION,
};

/** timer resolution */
using kTimerResolution = std::chrono::microseconds;
constexpr const char* kMicrosecondStr = "µs";

template <typename Executor>
void execute_part(Executor exe, std::istream& input, bool verbose, bool time_execution)
{
  input.clear();
  input.seekg(0);

  auto start = std::chrono::steady_clock::now();
  std::cout << exe(input, verbose) << '\n';
  auto delta = std::chrono::steady_clock::now() - start;

  if (time_execution) {
    auto exe_duration = std::chrono::duration_cast<kTimerResolution>(delta);
    std::cout << exe_duration.count() << ' ' << kMicrosecondStr << '\n';
  }
}

void print_usage(int argc, char* argv[])
{
  std::cerr << "Invalid num args. Expected: " << Args::NUM_REQUIRED-1
            << " got " << argc-1 << '\n'
            << "usage: " << argv[Args::PROCESS_NAME] << " <filename> [<verbose>] [<timing>]\n"
            << "\tfilename - name of input file containing data\n"
            << "Optional:\n"
            << "\tverbose  - verbosity (0=off, 1=print) (Default 0)\n"
            << "\ttiming   - print execution time (0=off, 1=print) (Default 0)\n";
}

int main(int argc, char* argv[]) {
  // check input argument count
  if (argc < Args::NUM_REQUIRED) {
    print_usage(argc, argv);
    return EXIT_FAILURE;
  }

  // data file
  const char* filename = argv[Args::FILENAME];

  // verbosity
  bool kDefaultVerbosity = false;
  bool verbose = (argc > Args::VERBOSE) ? std::stoi(argv[Args::VERBOSE]) : kDefaultVerbosity;

  // timing
  bool kDefaultTiming = false;
  bool time_execution = (argc > Args::TIME_EXECUTION) ? std::stoi(argv[Args::TIME_EXECUTION]) : kDefaultTiming;

  if (verbose) {
    std::cout << "File: " << filename << '\n';
  }

  std::ifstream in(filename);
  if (!in) {
    std::cerr << "ERROR: Unable to open " << filename << '\n';
    return EXIT_FAILURE;
  }

  // Start timer
  auto start = std::chrono::steady_clock::now();

  // Part 1
  execute_part(aoc::part1, in, verbose, time_execution);

  // Part 2
  execute_part(aoc::part2, in, verbose, time_execution);

  auto delta = std::chrono::steady_clock::now() - start;
  if (time_execution) {
    auto exe_duration = std::chrono::duration_cast<kTimerResolution>(delta);
    std::cout << "Total: " << exe_duration.count() << ' ' << kMicrosecondStr << '\n';
  }

  return EXIT_SUCCESS;
}

