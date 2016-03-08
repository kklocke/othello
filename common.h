#ifndef __COMMON_H__
#define __COMMON_H__

enum Side { 
    WHITE, BLACK
};

class Move {
   
public:
    int x, y;
    Move(int x, int y) {
        this->x = x;
        this->y = y;        
    }
    ~Move() {}

    int getX() { return x; }
    int getY() { return y; }

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    // Check if a move is in the corner
    bool isCorner() {
        if ((x != 0) || (x != 7)) {
            return false;
        }
        if ((y != 0) || (y != 7)) {
            return false;
        }
        return true;
    }
    // Check if a move is by a corner
    bool isByCorner() {
        if ((x == 0) || (x == 7)) {
            if ((y == 1) || (y == 6)) {
                return true;
            }
        }
        if ((x == 1) || (x == 6)) {
            if ((y == 0) || (y == 7) || (y == 1) || (y == 6)) {
                return true;
            }
        }
        return false;
    }
    // Check if a move is on a wall
    bool isWall() {
        if ((x == 0) || (x == 7) || (y == 0) || (y == 7)) {
            return true;
        }
        return false;
    }
};

#endif
