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

#include <cassert>
#include <iostream>

#include "game.h"
#include "dumb_ai_player.h"
#include "human_player.h"
#include "tree_ai_player.h"

int main() {
  std::cout << "tic-tac-ai" << std::endl;

  Game game;

  TreeAIPlayer* smartPlayer = new TreeAIPlayer;
  smartPlayer->setIsTraining(true);

  game.setPlayer1(smartPlayer);
  game.setPlayer2(new DumbAIPlayer);

  for (auto i = 0; i < 100000; ++i) {
    if (i % 1000 == 0) {
      std::cout << i << "\r";
    }
    game.play(false, std::cout);
  }

  // Now play against the trained AI.
  smartPlayer->setIsTraining(false);
  game.setPlayer2(new HumanPlayer);
  game.play(true);

  return 0;
}
