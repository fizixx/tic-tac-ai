# tic-tac-ai

Tic Tac Toe AI experiment.

The game has 4 types of players:

### Human player

This player is controlled by a human.

### Dumb AI player

This player selects a random block to play.  This is a good opponent for the learning AI.

### Strategic AI player

This player selects his moves from a set of simple rules.  If he can win then he wins.  If he's about to lose, try to block the opponent.  Otherwise try to complete a half filled row/diagonal.

### Learning AI player (Tree AI player)

This player learns how to play the game.  It is based on a decision tree with scores depending on the success of a move from the current node.  This player has to be learned how to play first.
