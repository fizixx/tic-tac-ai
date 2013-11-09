
#ifndef TREE_AI_PLAYER_H_
#define TREE_AI_PLAYER_H_

#include "player.h"

class TreeAIPlayer : public Player {
public:
  TreeAIPlayer();
  virtual ~TreeAIPlayer();

  virtual size_t GetMove(const Board& board, bool previousMoveWasValid);
  virtual void AfterMove(const Board& board);
  virtual void ReportWinner(const Board& board);

private:
  struct BoardNode;

  // Given a |parentNode|, find a child node who's board is the same as the
  // given |board|.
  BoardNode* FindBoardInNode(BoardNode* parentNode, const Board& board) const;

  // Play a move we haven't encountered before.  |board| is the current board we
  // are playing against.
  void PlayUnknownMove(const Board& board);

  // The root of all the board nodes.
  BoardNode* _rootNode;

  // The current node we are looking at.
  BoardNode* _currentNode;

  // The node we played last.
  bool _lastMoveWasUnknown;
};

#endif  // PLAYER_H_
