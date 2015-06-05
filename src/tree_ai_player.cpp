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

#include "tree_ai_player.h"

#include <cassert>
#include <iostream>
#include <vector>

struct TreeAIPlayer::BoardNode {
  BoardNode* parent{nullptr};
  BoardNode* firstChild{nullptr};
  BoardNode* next{nullptr};

  Board board;

  BoardNode(BoardNode* parent) : parent(parent) {}
};

TreeAIPlayer::TreeAIPlayer() : m_rootNode(new BoardNode{nullptr}) {
}

TreeAIPlayer::~TreeAIPlayer() {
}

size_t TreeAIPlayer::getMove(const Board& board, bool previousMoveWasValid) {
  if (board.isEmpty()) {
    // If the board is empty, then we are the first player and we make the
    // |m_rootNode| the |m_currentNode|, as if it was played the previous round.
    m_currentNode = m_rootNode;
  } else {
    // If the board is not empty, we see if we've encountered this board before.
    if (m_currentNode)
      m_currentNode = FindBoardInNode(m_currentNode, board);
  }

  // If the |m_currentNode| is not set yet, it means we haven't seen this board
  // before and we just play a random move.
  if (!m_currentNode)
    return board.getFirstOpenCell();

  // Revert back to a random pick.
  return board.getFirstOpenCell();
}

void TreeAIPlayer::afterMove(const Board& board) {
  std::cout << "AfterMove(...)" << std::endl;
}

void TreeAIPlayer::reportWinner(const Board& board) {
  std::cout << "TreeAIPlayer::ReportWinner(...)" << std::endl;
}

TreeAIPlayer::BoardNode* TreeAIPlayer::FindBoardInNode(
    BoardNode* parentNode, const Board& board) const {
  BoardNode* node = parentNode->firstChild;
  for (BoardNode* node = parentNode->firstChild; node; node = node->next) {
    if (node->board == board)
      return node;
  }
  return nullptr;
}

void TreeAIPlayer::PlayUnknownMove(const Board& board) {
  // Find the last node so that we can set it's next node.
  BoardNode* lastNode = m_currentNode->firstChild;
  for (; lastNode; lastNode = lastNode->next) {
  }

  size_t newMove = board.getFirstOpenCell();
  BoardNode* newNode = new BoardNode{m_currentNode};
  newNode->board = board;

  if (!m_currentNode->firstChild)
    m_currentNode->firstChild = newNode;

  if (lastNode)
    lastNode->next = newNode;

  m_currentNode = newNode;
}
