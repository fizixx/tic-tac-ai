
#ifndef PLAYER_H_
#define PLAYER_H_

#include "board.h"

class Player {
public:
	virtual ~Player();
	
	virtual size_t GetMove(const Board& board, bool previousMoveWasValid) = 0;
	virtual void ReportWinner(const Board& board) = 0;
};

#endif  // PLAYER_H_
