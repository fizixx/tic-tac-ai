
#include "dumb_ai_player.h"

DumbAIPlayer::DumbAIPlayer() {
	srand(time(NULL));
}

DumbAIPlayer::~DumbAIPlayer() {
}

size_t DumbAIPlayer::GetMove(const Board& board, bool previousMoveWasValid) {
	return rand() % 9;
}

void DumbAIPlayer::ReportWinner(const Board& board) {
}
