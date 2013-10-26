
#include "game.h"
#include <cassert>

Game::Game()
	: _currentPlayer(PLAYER_UNKNOWN), _player1(0), _player2(0) {
}

Game::~Game() {
}

void Game::SetPlayer1(Player* player) {
	_player1 = player;
}

void Game::SetPlayer2(Player* player) {
	_player2 = player;
}

void Game::Play(std::ostream& os) {
	_currentPlayer = PLAYER_1;
	
	// Cannot start game without players.
	assert(_player1);
	assert(_player2);
	
	PlayerType winner = PLAYER_UNKNOWN;

	for (;;) {
		_board.Print(os, true);
		
		char move = -1;
		switch (_currentPlayer) {
			case PLAYER_1:
				os << "Player 1 (X)" << std::endl;
				move = _player1->GetMove(_board, true);
				while (!_board.SetMove(move, 'X'))
					move = _player1->GetMove(_board, false);
				_currentPlayer = PLAYER_2;
				break;
				
			case PLAYER_2:
				os << "Player 2 (O)" << std::endl;
				move = _player2->GetMove(_board, true);
				while (!_board.SetMove(move, 'O'))
					move = _player2->GetMove(_board, false);
				_currentPlayer = PLAYER_1;
				break;
				
			default:
				break;
		}
		
		char winnerCell = _board.GetWinner();
		if (winnerCell == 'X') {
			winner = PLAYER_1;
			break;
		} else if (winnerCell == 'O') {
			winner = PLAYER_2;
			break;
		} else if (_board.IsFull())
			break;
	}
	
	// Print the final board without instructions.
	_board.Print(os, false);
	
	if (winner == PLAYER_1) {
		_player1->ReportWinner(_board);
		os << "Player 1 wins!" << std::endl;
	}
	else if (winner == PLAYER_2) {
		_player2->ReportWinner(_board);
		os << "Player2 wins!" << std::endl;
	} else {
		os << "Game is a draw!" << std::endl;
	}
}
