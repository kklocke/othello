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
    Move *computeMinimax();
    int recurMinimax(Board *board, int depth, int maxDepth, Side play, Side watch);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

    Board *board;
    Move *move; //for global storage of current move 
    Side side;
    Side other;
};

#endif
