
#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "player.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	virtual ~HumanPlayer();
	
	// Override: Player
	virtual size_t GetMove(const Board& board, bool previousMoveWasValid);
	virtual void ReportWinner(const Board& board);
};

#endif  // HUMAN_PLAYER_H_
