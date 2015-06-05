
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

void Board::Print(std::ostream& os, bool instructions) const {
  os << ' ' << GetCell(0, instructions) << " | " << GetCell(1, instructions)
     << " | " << GetCell(2, instructions) << ' ' << std::endl;
  os << "---+---+---" << std::endl;
  os << ' ' << GetCell(3, instructions) << " | " << GetCell(4, instructions)
     << " | " << GetCell(5, instructions) << ' ' << std::endl;
  os << "---+---+---" << std::endl;
  os << ' ' << GetCell(6, instructions) << " | " << GetCell(7, instructions)
     << " | " << GetCell(8, instructions) << ' ' << std::endl;
}

bool Board::SetMove(size_t position, char player) {
  // If there is already something in that position, then we can't make that
  // move.
  if (m_board[position] != ' ')
    return false;

  m_board[position] = player;
  return true;
}

bool Board::IsEmpty() const {
  // The board is empty if if there are open spaces.
  return std::count(std::begin(m_board), std::end(m_board), ' ') != 0;
}

bool Board::IsFull() const {
  // The board is full if there are no more open spaces.
  return std::count(std::begin(m_board), std::end(m_board), ' ') == 0;
}

size_t Board::GetFirstOpenCell() const {
  for (size_t i = 0; i < m_board.size(); ++i) {
    if (m_board[i] == ' ') {
      return i;
    }
  }

  return m_board.size();
}

char Board::GetWinner() const {
  if (IsWinner(0, 1, 2))
    return m_board[0];

  if (IsWinner(3, 4, 5))
    return m_board[3];

  if (IsWinner(6, 7, 8))
    return m_board[4];

  if (IsWinner(0, 3, 6))
    return m_board[0];

  if (IsWinner(1, 4, 7))
    return m_board[1];

  if (IsWinner(2, 5, 8))
    return m_board[5];

  if (IsWinner(0, 4, 8))
    return m_board[0];

  if (IsWinner(2, 4, 6))
    return m_board[2];

  return ' ';
}

bool Board::IsWinner(size_t pos1, size_t pos2, size_t pos3) const {
  if (m_board[pos1] == ' ')
    return false;

  if (m_board[pos1] != m_board[pos2])
    return false;

  if (m_board[pos2] != m_board[pos3])
    return false;

  return true;
}

char Board::GetCell(size_t position, bool instructions) const {
  if (m_board[position] == ' ' && instructions)
    return '0' + position;
  return m_board[position];
}
