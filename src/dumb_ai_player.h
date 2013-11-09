
#ifndef DUMB_PLAYER_H_
#define DUMB_PLAYER_H_

#include "player.h"
#include "board.h"

class DumbAIPlayer : public Player {
public:
  DumbAIPlayer();
  virtual ~DumbAIPlayer();

  virtual size_t GetMove(const Board& board, bool previousMoveWasValid);
  virtual void AfterMove(const Board& board);
  virtual void ReportWinner(const Board& board);
};

#endif  // DUMB_PLAYER_H_
