// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "strategy_ai_player.h"

namespace {

// clang-format off
const size_t kWins[][3] = {
  {0, 1, 2},
  {3, 4, 5},
  {6, 7, 8},

  {0, 3, 6},
  {1, 4, 7},
  {2, 5, 8},

  {0, 4, 8},
  {2, 4, 6},
};
// clang-format on

size_t isPossibleWin(const Board& board, const size_t* pos, char you) {
  bool yes[3];
  for (size_t i = 0; i < 3; ++i) {
    yes[i] = (board.getMove(pos[i]) == you);
  }

  if (yes[0] && yes[1] && board.getMove(pos[2]) == ' ') {
    return pos[2];
  }

  if (yes[0] && yes[2] && board.getMove(pos[1]) == ' ') {
    return pos[1];
  }

  if (yes[1] && yes[2] && board.getMove(pos[0]) == ' ') {
    return pos[0];
  }

  return 99;
}

size_t isPossibleLose(const Board& board, const size_t* pos, char you) {
  bool yes[3];
  for (size_t i = 0; i < 3; ++i) {
    yes[i] = (board.getMove(pos[i]) != you && board.getMove(pos[i]) != ' ');
  }

  if (yes[0] && yes[1] && board.getMove(pos[2]) == ' ') {
    return pos[2];
  }

  if (yes[0] && yes[2] && board.getMove(pos[1]) == ' ') {
    return pos[1];
  }

  if (yes[1] && yes[2] && board.getMove(pos[0]) == ' ') {
    return pos[0];
  }

  return 99;
}

size_t isTowardsAWin(const Board& board, const size_t* pos, char you) {
  bool yes[3];
  for (size_t i = 0; i < 3; ++i) {
    yes[i] = (board.getMove(pos[i]) == you);
  }

  for (size_t i = 0; i < 3; ++i) {
    if (yes[i]) {
      for (size_t j = 0; j < 3; ++j) {
        if (i != j && board.getMove(pos[j]) == ' ') {
          return pos[j];
        }
      }
    }
  }

  return 99;
}

}  // namespace

StrategyAIPlayer::StrategyAIPlayer() {
}

StrategyAIPlayer::~StrategyAIPlayer() {
}

size_t StrategyAIPlayer::getMove(const Board& board, char you) {
  // If we start, play the center.
  if (board.isEmpty()) {
    return 4;
  }

  // First, check if we can win right now!
  for (int i = 0; i < 8; ++i) {
    size_t possible = isPossibleWin(board, kWins[i], you);
    if (possible != 99) {
      return possible;
    }
  }

  // Check if the other guy is about to win.
  for (int i = 0; i < 8; ++i) {
    size_t possible = isPossibleLose(board, kWins[i], you);
    if (possible != 99) {
      return possible;
    }
  }

  // Check if we can now play the center.
  if (board.getMove(4) == ' ') {
    return 4;
  }

  // Check where we have 1 block filled and then play one of the other two.
  for (int i = 0; i < 8; ++i) {
    size_t possible = isTowardsAWin(board, kWins[i], you);
    if (possible != 99) {
      return possible;
    }
  }

  return rand() % 9;
}

void StrategyAIPlayer::reportWinner(const Board& board, WinType winType) {
}
