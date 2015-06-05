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

  // The board at this stage of the tree.
  Board board;

  // The move that was played by the player.
  size_t movePlayed{9};

  // The winning score of this chain of nodes.
  int score{0};

  void appendChild(BoardNode* newNode) {
    newNode->parent = this;
    if (!firstChild) {
      firstChild = newNode;
    } else {
      // Find our last child node.
      for (BoardNode* node = firstChild; node; node = node->next) {
        if (!node->next) {
          node->next = newNode;
          break;
        }
      }
    }
  }
};

TreeAIPlayer::TreeAIPlayer() : m_rootNode(new BoardNode) {
}

TreeAIPlayer::~TreeAIPlayer() {
}

size_t TreeAIPlayer::getMove(const Board& board, char you,
                             bool previousMoveWasValid) {
  // If the board is empty, it means we're the first one to make a move in this
  // game.
  if (board.isEmpty()) {
    // If we're the first to play, we should not have a current node yet.
    assert(!m_currentNode);

    // The root node is an empty board, so we set that as our current node.
    m_currentNode = m_rootNode;
  } else {
    // If there is no current node, it means we are not the first player in the
    // game and the other player has started.  We set the current node to the
    // root node, so that we can search for the other player's move from the
    // empty board.
    if (!m_currentNode) {
      m_currentNode = m_rootNode;
    }

    // Find the move that the other player made from the current node.
    BoardNode* foundNode = findBoardInNode(m_currentNode, board);

    // If we can't find the other player's board, then it means we haven't
    // encountered that move yet, so we have to log it.  Otherwise we use the
    // node that we found.
    m_currentNode = foundNode ? foundNode : logOtherMove(m_currentNode, board);
  }

  // We should have a current node now.
  assert(m_currentNode);

  // Select the best move, starting from the root/current node.
  size_t bestMove = getBestMoveForNode(m_currentNode);

  // Log the new move and set the new current to the new node.
  m_currentNode = logMove(m_currentNode, board, bestMove, you);

  return bestMove;
}

void TreeAIPlayer::reportWinner(const Board& winningBoard, bool won) {
  // If the current node isn't the move that won the game, then we have to log
  // the other player's move.
  if (m_currentNode->board != winningBoard) {
    m_currentNode = logOtherMove(m_currentNode, winningBoard);
  }

  // Now the current node is pointing to the node that won/lost the game, so if
  // we won, add a win to the score.
  for (BoardNode* current = m_currentNode; current; current = current->parent) {
    current->score += 2;
  }

  // When there was a winner, we reset our state.
  m_currentNode = nullptr;
}

TreeAIPlayer::BoardNode* TreeAIPlayer::findBoardInNode(
    BoardNode* parentNode, const Board& board) const {
  for (BoardNode* node = parentNode->firstChild; node; node = node->next) {
    if (node->board == board) {
      return node;
    }
  }
  return nullptr;
}

size_t TreeAIPlayer::getBestMoveForNode(BoardNode* startingNode) {
  // Find the node with the highest score.
  BoardNode* bestNode = nullptr;
  int bestScore = 0;
  int childCount = 0;
  for (BoardNode* current = startingNode->firstChild; current;
       current = current->next) {
    if (current->score > bestScore) {
      bestScore = current->score;
      bestNode = current;
    }
    ++childCount;
  }

  // If we can't get a high score node or we haven't played all the options yet,
  // return a "random" choice.
  if (childCount < 9 || !bestNode) {
    return startingNode->board.getFirstOpenCell();
  }

  assert(bestNode);
  // It should be a valid move.
  assert(bestNode->movePlayed != 9);

  return bestNode->movePlayed;
}

TreeAIPlayer::BoardNode* TreeAIPlayer::logMove(BoardNode* parentNode,
                                               const Board& board, size_t move,
                                               char you) {
  // The board that we received should match the node that we're at now's board.
  assert(parentNode->board == board);

  // Create a new board that includes the move that we are logging.
  Board newBoard = board;
  newBoard.setMove(move, you);

  // Check to see if we played this move before.
  BoardNode* foundNode = findBoardInNode(parentNode, newBoard);
  
  // If we already played this move, then this is the node we return.
  if (foundNode) {
    return foundNode;
  }

  // We haven't played this move before, so we have to add it.
  BoardNode* newNode = new BoardNode;
  newNode->board = newBoard;
  newNode->movePlayed = move;
  parentNode->appendChild(newNode);

  // Return the new node.
  return newNode;
}

TreeAIPlayer::BoardNode* TreeAIPlayer::logOtherMove(BoardNode* parentNode,
                                                    const Board board) {
  // Check to see if we haven't already encountered the other player's move.
  BoardNode* foundNode = findBoardInNode(parentNode, board);
  
  // If we have, then we return this one as the new node.
  if (foundNode) {
    return foundNode;
  }

  // Otherwise, we have to create a new node for the new move.
  BoardNode* newNode = new BoardNode;
  newNode->board = board;
  parentNode->appendChild(newNode);

  // Return the new node.
  return newNode;
}
