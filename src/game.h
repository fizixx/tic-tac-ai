
#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "player.h"

class Game {
public:
	Game();
	~Game();

	void SetPlayer1(Player* player);
	void SetPlayer2(Player* player);
	
	void Play(std::ostream& os);
	
private:
	enum PlayerType {
		PLAYER_UNKNOWN,
		PLAYER_1,
		PLAYER_2,
	};
	
	PlayerType _currentPlayer;
	
	Board _board;
	Player* _player1;
	Player* _player2;
};

#endif  // GAME_H_
