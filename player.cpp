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
    move = NULL;
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
    Move *myMove = computeMinimax();
    //recurMinimax(board, 0, 4, side, other);
    if (myMove != NULL) {
        board->doMove(myMove, side);
    }
    //Move *myMove = new Move(move->getX(), move->getY());
    return myMove;
}


Move *Player::computeMinimax() {
    std::vector<Move> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move myMove(i, j);
            if (board->checkMove(&myMove, side)) {
                moves.push_back(myMove);
            }
        }
    }
    Board *myBoard = NULL;
    int indexBestMove = -1;
    int scoreBestMove = std::numeric_limits<int>::min();
    for (int a = 0; a < (int)moves.size(); a++) {
        myBoard = board->copy();
        myBoard->doMove(&moves[a], side);
        int worst = std::numeric_limits<int>::max();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move myMove(i, j);
                if (myBoard->checkMove(&myMove, other)) {
                    Board *tryBoard = myBoard->copy();
                    tryBoard->doMove(&myMove, other);
                    int tryScore = tryBoard->heuristic(side, other, testingMinimax);
                    if (tryScore < worst) {
                        worst = tryScore;
                    }
                    delete tryBoard;
                }
            }
        }
        delete myBoard;
        if (worst > scoreBestMove) {
            scoreBestMove = worst;
            indexBestMove = a;
        }
    }
    if (indexBestMove != -1) {
        Move *toMove = new Move(moves[indexBestMove].getX(), moves[indexBestMove].getY());
        return toMove;
    }
    return NULL;
}


/*int Player::recurMinimax(Board *board, int depth, int maxDepth, Side play, Side watch) {
    if (depth == maxDepth) {
        int score = board->heuristic(side, other, testingMinimax);
        return score;
    }
    int worst = std::numeric_limits<int>::max();
    Move worstMove(-1, -1);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move move(i, j);
            if (board->checkMove(&move, play)) {
                Board *tryBoard = board->copy();
                tryBoard->doMove(&move, play);
                int score = recurMinimax(tryBoard, depth + 1, maxDepth, watch, play);
                if (score < worst) {
                    worst = score;
                    worstMove = move;
                }
                delete tryBoard;
            }
        }
    }




    if (depth == 0) {
        if (this->move != NULL) {
            delete this->move;
        }
        if ((worstMove.getX() != -1)) {
            this->move = new Move(worstMove.getX(), worstMove.getY());
        }
    }

    // if there were no possible moves:
    if (worstMove.getX() == -1) {
        // no move was made
        // want to indicate this
        // good enough to just return score of current board
        return board->heuristic(side, other, testingMinimax);
    }

    return worst;
}*/
