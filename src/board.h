
#ifndef BOARD_H_
#define BOARD_H_

#include <ostream>

class Board {
public:
  Board();
  Board(const Board& other);
  ~Board();

  Board& operator=(const Board& other);

  bool operator==(const Board& other) const;
  bool operator!=(const Board& other) const;

  void Print(std::ostream& os, bool instructions) const;

  bool SetMove(size_t position, char player);

  bool IsEmpty() const;
  bool IsFull() const;

  size_t GetFirstOpenCell() const;

  char GetWinner() const;

private:
  enum {
    kNumberOfCells = 9
  };

  char GetCell(size_t position, bool instructions) const;
  bool IsWinner(size_t pos1, size_t pos2, size_t pos3) const;

  char _board[kNumberOfCells];
};

#endif  // BOARD_H_
