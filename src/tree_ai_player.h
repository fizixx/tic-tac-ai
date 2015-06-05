// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef TREE_AI_PLAYER_H_
#define TREE_AI_PLAYER_H_

#include "player.h"

class TreeAIPlayer : public Player {
public:
  TreeAIPlayer();
  ~TreeAIPlayer() override;

  // Set whether the player is training of playing.
  void setIsTraining(bool isTraining);

  size_t getMove(const Board& board, char you, bool previousMoveWasValid) override;
  void reportWinner(const Board& board, bool won) override;

private:
  struct BoardNode;

  // Given a |parentNode|, find a child node who's board is the same as the
  // given |board|.
  BoardNode* findBoardInNode(BoardNode* parentNode, const Board& board) const;

  // Play a move we haven't encountered before.  |board| is the current board we
  // are playing against.
  void playUnknownMove(const Board& board);

  size_t getBestMoveForNode(BoardNode* startingNode);

  // Log the current move in our database of moves.  Returns the newly inserted
  // node.
  BoardNode* logMove(BoardNode* node, const Board& board, size_t move,
                     char you);

  // Log a move from the other player.
  BoardNode* logOtherMove(BoardNode* node, const Board board);

  // The root of all the board nodes.
  BoardNode* m_rootNode;

  // The current node we are looking at.
  BoardNode* m_currentNode{nullptr};

  // Whether the player is playing or training.
  bool m_isTraining{false};
};

#endif  // PLAYER_H_
