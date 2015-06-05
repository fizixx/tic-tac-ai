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

#ifndef BOARD_H_
#define BOARD_H_

#include <array>
#include <ostream>

class Board {
public:
  Board();

  bool operator==(const Board& other) const;
  bool operator!=(const Board& other) const;

  void print(std::ostream& os, bool instructions) const;

  char getMove(size_t position) const { return m_board[position]; }
  bool setMove(size_t position, char player);

  bool isEmpty() const;
  bool isFull() const;

  size_t getFirstOpenCell() const;

  char getWinner() const;

private:
  char getCell(size_t position, bool instructions) const;
  bool isWinner(size_t pos1, size_t pos2, size_t pos3) const;

  std::array<char, 9> m_board;
};

#endif  // BOARD_H_
