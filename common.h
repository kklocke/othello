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
    bool isCorner() {
        if ((x != 0) || (x != 7)) {
            return false;
        }
        if ((y != 0) || (y != 7)) {
            return false;
        }
        return true;
    }

    bool isByCorner() {
        if ((x == 0) || (x == 7)) {
            if ((y == 1) || (y == 6)) {
                return true;
            }
        }
        if ((x == 1) || (x == 6)) {
            if ((y == 0) || (y == 7)) {
                return true;
            }
        }
        return false;
    }

    bool isWall() {
        if ((x == 0) || (x == 7) || (y == 0) || (y == 7)) {
            return true;
        }
        return false;
    }
};

#endif
