#include "player.h"
#include <limits>
#include <cstdio>

// GIT HYPED FOR OTHELLO BOIS
Move *myMove = NULL;
/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    this->side = side;
    other = (this->side == BLACK) ? WHITE : BLACK;
    board = new Board;
    testingMinimax = false;
    if (side == BLACK) {
        fprintf(stderr, "PLAYER IS BLACK\n");
    }
    else {
        fprintf(stderr, "PLAYER IS WHITE\n");
    }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
	delete move;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

	if (opponentsMove != NULL) {
        board->doMove(opponentsMove, other);
    }
    Move maxMove(-1,-1);
    Board *workingBoard;
    int maxScore = std::numeric_limits<int>::min();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move tryMove = Move(i,j);
            if (board->checkMove(&tryMove, side)) {
                workingBoard = board->copy();
                workingBoard->doMove(&tryMove, side);
                int myScore = workingBoard->count(side) - workingBoard->count(other);
                if (tryMove.isCorner()) {
                    myScore *= 3;
                }
                else if (tryMove.isByCorner()) {
                    myScore *= -3;
                }
                else if (tryMove.isWall()) {
                    myScore *= 2;
                }
                if (myScore > maxScore) {
                    maxScore = myScore;
                    maxMove.setX(i);
                    maxMove.setY(j);
                }
                delete workingBoard;
            }
        }
    }
    if ((maxMove.getX() != -1) && (maxMove.getY() != -1)) {
        myMove = new Move(maxMove.getX(), maxMove.getY());
    }
    else {
        myMove = NULL;
    }
    board->doMove(myMove, side);

    return myMove;
}


Move *Player::computeMinimax(std::vector<Move> movelist) {
	if(movelist.size() == 0)
		return NULL;
	int n = movelist.size();
	Board *firstLayer = new Board[n];
	int *worst_scores = new int[n];
	for (unsigned int i = 0; i < movelist.size(); i++) {
		firstLayer[i] = *(board->copy());
        firstLayer[i].doMove(&movelist[i], side);
        worst_scores[i] = std::numeric_limits<int>::max();
    }
    Board **secondLayer = new Board*[movelist.size()];
	for (unsigned int i = 0; i < movelist.size(); i++) {
		std::vector<Move> secondLayerMoves = firstLayer[i].validMoves(other);
	    secondLayer[i] = new Board[secondLayerMoves.size()];
	    for (unsigned int j = 0; j < secondLayerMoves.size(); j++) {
	    	secondLayer[i][j] = *(firstLayer[i].copy());
	    	secondLayer[i][j].doMove(&secondLayerMoves[j], other);
	    	int score = secondLayer[i][j].count(side) - secondLayer[i][j].count(other);
	    	std::cerr << "score: " << score << std::endl;
	    	if(score < worst_scores[i]){
	    		worst_scores[i] = score;
	    	}
	    }
	}
	int best_score = worst_scores[0];
	this->move = new Move(movelist[0].getX(), movelist[0].getY());
	for (unsigned int i = 1; i < movelist.size(); i++) {
		if(worst_scores[i] > best_score)
			this->move = new Move(movelist[i].getX(), movelist[i].getY());
    }
    delete[] firstLayer;
    delete[] secondLayer;
    delete[] worst_scores;
    return this->move;
}

