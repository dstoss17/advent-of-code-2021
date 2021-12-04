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
#include "aoc/image.h"

using BingoBoard = std::array<int, 25>;
using BingoMarker = std::array<bool, 25>;

struct BingoGame {
  std::vector<int> tokens;
  std::vector<BingoBoard> boards;
};

BingoGame load_game(std::istream& in)
{
  BingoGame game;

  // first line is a comma-separate list of moves
  std::string line;
  std::getline(in, line);
  std::istringstream iss(line);
  while (iss) {
    int tmp;
    iss >> tmp;
    game.tokens.push_back(tmp);
    iss.ignore(1, ',');
  }

  BingoBoard tmp;
  int nline = 0;
  while (std::getline(in, line)) {
    if (line.empty()) { continue; }
    std::istringstream lin(line);
    lin >> tmp[nline * 5] >> tmp[nline * 5 + 1] >> tmp[nline * 5 + 2] >> tmp[nline * 5 + 3] >> tmp[nline * 5 + 4];
    nline++;
    if (nline == 5) {
      game.boards.push_back(tmp);
      nline = 0;
    }
  }

  return game;
}

void mark_boards(int token, const std::vector<BingoBoard>& boards, std::vector<BingoMarker>* markers)
{
  size_t num_boards = boards.size();
  std::vector<BingoMarker>& rmarkers = *markers;
  for (size_t ii = 0; ii != num_boards; ii++) {
    for (size_t jj = 0; jj != boards[ii].size(); jj++) {
      if (boards[ii][jj] == token) {
        rmarkers[ii][jj] = true;
        break;
      }
    }
  }
}

bool check_winner(const BingoMarker& markers)
{
  bool r1 = (markers[0] && markers[1] && markers[2] && markers[3] && markers[4]);
  bool r2 = (markers[5] && markers[6] && markers[7] && markers[8] && markers[9]);
  bool r3 = (markers[10] && markers[11] && markers[12] && markers[13] && markers[14]);
  bool r4 = (markers[15] && markers[16] && markers[17] && markers[18] && markers[19]);
  bool r5 = (markers[20] && markers[21] && markers[22] && markers[23] && markers[24]);
  bool c1 = (markers[0] && markers[5] && markers[10] && markers[15] && markers[20]);
  bool c2 = (markers[1] && markers[6] && markers[11] && markers[16] && markers[21]);
  bool c3 = (markers[2] && markers[7] && markers[12] && markers[17] && markers[22]);
  bool c4 = (markers[3] && markers[8] && markers[13] && markers[18] && markers[23]);
  bool c5 = (markers[4] && markers[9] && markers[14] && markers[19] && markers[24]);

  return (r1 || r2 || r3 || r4 || r5 || c1 || c2 || c3 || c4 || c5);
}

int compute_score(int token, const BingoBoard& board, const BingoMarker& marker)
{
  int sum = 0;
  for (size_t ii = 0; ii != board.size(); ii++) {
    if (!marker[ii]) {
      sum += board[ii];
    }
  }

  return token * sum;
}

int play_game(const BingoGame& game)
{
  std::vector<BingoMarker> markers(game.boards.size());
  size_t max_rounds = game.tokens.size();

  for (size_t ii = 0; ii != max_rounds; ii++) {
    int token = game.tokens[ii];
    mark_boards(token, game.boards, &markers);
    for (size_t jj = 0; jj != markers.size(); jj++) {
      if (check_winner(markers[jj])) {
        return compute_score(token, game.boards[jj], markers[jj]);
      }
    }
  }

  return -1;
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto game = load_game(in);
  std::ostringstream out;
  out << play_game(game);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  std::ostringstream out;
  out << "Not implemented";
  return out.str();
}

} // namespace aoc
