
#include "game.h"
#include "dumb_ai_player.h"
#include "human_player.h"
#include <cassert>
#include <iostream>

int main() {
	std::cout << "tic-tac-ai" << std::endl;

	// HumanPlayer
	Game game;
	game.SetPlayer1(new DumbAIPlayer());
	game.SetPlayer2(new DumbAIPlayer());
	
	game.Play(std::cout);
	
	return 0;
}