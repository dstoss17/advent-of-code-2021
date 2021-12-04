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
#include <limits>
#include <array>
#include "aoc/parts.h"
#include "aoc/utils.h"

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

void mark_board(int token, const BingoBoard& board, BingoMarker* marker)
{
  for (size_t ii = 0; ii != board.size(); ii++) {
    if (board[ii] == token) {
      (*marker)[ii] = true;
      return;
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

struct GameResult {
  int token;
  int rounds;
  BingoMarker markers;
};

GameResult simulate_game(const std::vector<int>& tokens, const BingoBoard& board)
{
  GameResult result {};
  size_t ii = 0;
  while (!check_winner(result.markers)) {
    result.token = tokens[ii];
    mark_board(result.token, board, &result.markers);
    ii++;
  }

  result.rounds = static_cast<int>(ii);
  return result;
}

int play_game(const BingoGame& game, bool first_winner)
{
  std::vector<GameResult> results;
  for (const auto& board : game.boards) {
    results.push_back(simulate_game(game.tokens, board));
  }

  size_t winner = 0;
  int winner_rounds = (first_winner) ? std::numeric_limits<int>::max() :std::numeric_limits<int>::min();
  for (size_t ii = 0; ii != results.size(); ii++) {
    if ((first_winner && results[ii].rounds < winner_rounds) ||
        (!first_winner && results[ii].rounds > winner_rounds)) {
      winner = ii;
      winner_rounds = results[ii].rounds;
    }
  }

  return compute_score(results[winner].token, game.boards[winner], results[winner].markers);
}

namespace aoc {

std::string part1(std::istream& in, bool verbose) {
  auto game = load_game(in);
  std::ostringstream out;
  out << play_game(game, true);
  return out.str();
}

std::string part2(std::istream& in, bool verbose) {
  auto game = load_game(in);
  std::ostringstream out;
  out << play_game(game, false);
  return out.str();
}

} // namespace aoc
