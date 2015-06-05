
#ifndef BOARD_H_
#define BOARD_H_

#include <array>
#include <ostream>

class Board {
public:
  Board();

  bool operator==(const Board& other) const;
  bool operator!=(const Board& other) const;

  void Print(std::ostream& os, bool instructions) const;

  bool SetMove(size_t position, char player);

  bool IsEmpty() const;
  bool IsFull() const;

  size_t GetFirstOpenCell() const;

  char GetWinner() const;

private:
  char GetCell(size_t position, bool instructions) const;
  bool IsWinner(size_t pos1, size_t pos2, size_t pos3) const;

  std::array<char, 9> m_board;
};

#endif  // BOARD_H_
