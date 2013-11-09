
#include "tree_ai_player.h"

#include <cassert>
#include <iostream>
#include <vector>

struct TreeAIPlayer::BoardNode {
  BoardNode* parent;
  BoardNode* firstChild;
  BoardNode* next;

  Board board;

  BoardNode() : parent(nullptr), firstChild(nullptr), next(nullptr) {}
};

TreeAIPlayer::TreeAIPlayer()
  : _rootNode(new BoardNode), _currentNode(nullptr) {}

TreeAIPlayer::~TreeAIPlayer() {}

size_t TreeAIPlayer::GetMove(const Board& board, bool previousMoveWasValid) {
  if (board.IsEmpty()) {
    // If the board is empty, then we are the first player and we make the
    // |_rootNode| the |_currentNode|, as if it was played the previous round.
    _currentNode = _rootNode;
  } else {
    // If the board is not empty, we see if we've encountered this board before.
    if (_currentNode)
      _currentNode = FindBoardInNode(_currentNode, board);
  }

  // If the |_currentNode| is not set yet, it means we haven't seen this board
  // before and we just play a random move.
  if (!_currentNode)
    return board.GetFirstOpenCell();

  // Revert back to a random pick.
  return board.GetFirstOpenCell();
}

void TreeAIPlayer::AfterMove(const Board& board) {
  std::cout << "AfterMove(...)" << std::endl;
}

void TreeAIPlayer::ReportWinner(const Board& board) {
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
  BoardNode* lastNode = _currentNode->firstChild;
  for (; lastNode; lastNode = lastNode->next) {
  }

  size_t newMove = board.GetFirstOpenCell();
  BoardNode* newNode = new BoardNode;
  newNode->board = board;
  newNode->parent = _currentNode;

  if (!_currentNode->firstChild)
    _currentNode->firstChild = newNode;

  if (lastNode)
    lastNode->next = newNode;

  _currentNode = newNode;
}
