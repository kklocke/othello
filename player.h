#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector>
#include <limits> 
#include "common.h"
#include "board.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);

<<<<<<< HEAD
    Move *computeMinimax(std::vector<Move> movelist);

=======
    Side side;
    Side other;
    Board *board;
>>>>>>> 72470f7e9c87ba505319301d98313cce20123120
    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Board *board;
    Move *move; //for global storage of current move 
    Side side;
    Side other;
};

#endif
