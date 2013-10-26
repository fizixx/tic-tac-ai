cmake_minimum_required(VERSION 2.8)
project("tic-tac-ai")

add_executable("tic-tac-ai"
  "src/main.cpp"
	"src/board.cpp"
	"src/board.h"
	"src/player.h"
	"src/player.cpp"
	"src/human_player.h"
	"src/human_player.cpp"
	"src/game.h"
	"src/game.cpp"
	"src/dumb_ai_player.h"
	"src/dumb_ai_player.cpp"
)

