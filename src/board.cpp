
#include "board.h"
#include <algorithm>
#include <cassert>

Board::Board() {
	std::fill(_board, _board + kNumberOfCells, ' ');
}

Board::Board(const Board& other) {
	std::copy(other._board, other._board + kNumberOfCells, _board);
}

Board::~Board() {
}

Board& Board::operator=(const Board& other) {
	std::copy(other._board, other._board + kNumberOfCells, _board);
	return *this;
}

bool Board::operator==(const Board& other) const {
	for (size_t i = 0; i < kNumberOfCells; ++i)
		if (_board[i] != other._board[i])
			return false;
	return true;
}

bool Board::operator!=(const Board& other) const {
	return !(*this == other);
}

void Board::Print(std::ostream& os, bool instructions) const {
	os << GetCell(0, instructions) << '|' << GetCell(1, instructions) << '|' << GetCell(2, instructions) << std::endl;
	os << "-+-+-" << std::endl;
	os << GetCell(3, instructions) << '|' << GetCell(4, instructions) << '|' << GetCell(5, instructions) << std::endl;
	os << "-+-+-" << std::endl;
	os << GetCell(6, instructions) << '|' << GetCell(7, instructions) << '|' << GetCell(8, instructions) << std::endl;
}

bool Board::SetMove(size_t position, char player) {
	if (position >= kNumberOfCells)
		return false;
	
	if (_board[position] != ' ')
		return false;
	
	_board[position] = player;
	return true;
}

bool Board::IsFull() const {
	return std::find(_board, _board + kNumberOfCells, ' ') == _board + kNumberOfCells;
}

char Board::GetWinner() const {
	if (IsWinner(0, 1, 2))
		return _board[0];
	
	if (IsWinner(3, 4, 5))
		return _board[3];
	
	if (IsWinner(6, 7, 8))
		return _board[4];
	
	if (IsWinner(0, 3, 6))
		return _board[0];
	
	if (IsWinner(1, 4, 7))
		return _board[1];
	
	if (IsWinner(2, 5, 8))
		return _board[5];
	
	if (IsWinner(0, 4, 8))
		return _board[0];
	
	if (IsWinner(2, 4, 6))
		return _board[2];
	
	return ' ';
}

bool Board::IsWinner(size_t pos1, size_t pos2, size_t pos3) const {
	if (_board[pos1] == ' ')
		return false;
	
	if (_board[pos1] != _board[pos2])
		return false;
	
	if (_board[pos2] != _board[pos3])
		return false;
	
	return true;
}

char Board::GetCell(size_t position, bool instructions) const {
	if (position > kNumberOfCells) {
		assert(false);
		return ' ';
	}
	
	if (_board[position] == ' ' && instructions)
		return '0' + position;
	return _board[position];
}
