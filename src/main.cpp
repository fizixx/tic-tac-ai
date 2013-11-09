
#include "game.h"
#include "dumb_ai_player.h"
#include "human_player.h"
#include "tree_ai_player.h"
#include <cassert>
#include <iostream>

int main() {
  std::cout << "tic-tac-ai" << std::endl;

  // HumanPlayer
  Game game;
  game.SetPlayer1(new TreeAIPlayer());
  game.SetPlayer2(new DumbAIPlayer());

  game.Play(std::cout);

  return 0;
}
