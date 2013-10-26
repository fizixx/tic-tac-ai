
#include "human_player.h"
#include <iostream>

HumanPlayer::HumanPlayer() {
}

HumanPlayer::~HumanPlayer() {
}

size_t HumanPlayer::GetMove(const Board& board, bool previousMoveWasValid) {
	std::cout << "Enter move: ";
	int move = 10;
	std::cin >> move;
	return move;
}

void HumanPlayer::ReportWinner(const Board& board) {
}
