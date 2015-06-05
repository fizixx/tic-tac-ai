cmake_minimum_required(VERSION 2.8)
project("tic-tac-ai")

add_executable("tic-tac-ai"
  "src/board.cpp"
  "src/board.h"
  "src/dumb_ai_player.cpp"
  "src/dumb_ai_player.h"
  "src/game.cpp"
  "src/game.h"
  "src/human_player.cpp"
  "src/human_player.h"
  "src/player.cpp"
  "src/player.h"
  "src/main.cpp"
  "src/strategy_ai_player.cpp"
  "src/strategy_ai_player.h"
  "src/tree_ai_player.cpp"
  "src/tree_ai_player.h"
)

