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

#include "board.h"
#include <algorithm>

Board::Board() {
  m_board.fill(' ');
}

bool Board::operator==(const Board& other) const {
  return m_board == other.m_board;
}

bool Board::operator!=(const Board& other) const {
  return !(*this == other);
}

void Board::print(std::ostream& os, bool instructions) const {
  os << ' ' << getCell(0, instructions) << " | " << getCell(1, instructions)
     << " | " << getCell(2, instructions) << ' ' << std::endl;
  os << "---+---+---" << std::endl;
  os << ' ' << getCell(3, instructions) << " | " << getCell(4, instructions)
     << " | " << getCell(5, instructions) << ' ' << std::endl;
  os << "---+---+---" << std::endl;
  os << ' ' << getCell(6, instructions) << " | " << getCell(7, instructions)
     << " | " << getCell(8, instructions) << ' ' << std::endl;
}

bool Board::setMove(size_t position, char player) {
  // If there is already something in that position, then we can't make that
  // move.
  if (m_board[position] != ' ')
    return false;

  m_board[position] = player;
  return true;
}

bool Board::isEmpty() const {
  // The board is empty if if there are open spaces.
  return std::count(std::begin(m_board), std::end(m_board), ' ') != 0;
}

bool Board::isFull() const {
  // The board is full if there are no more open spaces.
  return std::count(std::begin(m_board), std::end(m_board), ' ') == 0;
}

size_t Board::getFirstOpenCell() const {
  for (size_t i = 0; i < m_board.size(); ++i) {
    if (m_board[i] == ' ') {
      return i;
    }
  }

  return m_board.size();
}

char Board::getWinner() const {
  if (isWinner(0, 1, 2))
    return m_board[0];

  if (isWinner(3, 4, 5))
    return m_board[3];

  if (isWinner(6, 7, 8))
    return m_board[4];

  if (isWinner(0, 3, 6))
    return m_board[0];

  if (isWinner(1, 4, 7))
    return m_board[1];

  if (isWinner(2, 5, 8))
    return m_board[5];

  if (isWinner(0, 4, 8))
    return m_board[0];

  if (isWinner(2, 4, 6))
    return m_board[2];

  return ' ';
}

bool Board::isWinner(size_t pos1, size_t pos2, size_t pos3) const {
  if (m_board[pos1] == ' ')
    return false;

  if (m_board[pos1] != m_board[pos2])
    return false;

  if (m_board[pos2] != m_board[pos3])
    return false;

  return true;
}

char Board::getCell(size_t position, bool instructions) const {
  if (m_board[position] == ' ' && instructions)
    return '0' + position;
  return m_board[position];
}
