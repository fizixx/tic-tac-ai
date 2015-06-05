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

#ifndef GAME_H_
#define GAME_H_

#include <iostream>

#include "board.h"
#include "player.h"

class Game {
public:
  Game();

  void setPlayer1(Player* player);
  void setPlayer2(Player* player);

  void play(bool printSteps, std::ostream& os = std::cout);

private:
  enum PlayerType {
    PLAYER_UNKNOWN,
    PLAYER_1,
    PLAYER_2,
  };

  PlayerType m_currentPlayer;

  Board m_board;
  Player* m_player1;
  Player* m_player2;
};

#endif  // GAME_H_
