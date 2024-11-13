#ifndef PIECE_HPP
#define PIECE_HPP

#include "position.hpp"
#include <iostream>
using namespace std;

class Piece
{
private:
    int id;
    Position pos;
    bool isAte;
    bool isKing;

public:
    void setId(int id) { this->id = id; }
    void setPos(int x, int y)
    {
        this->pos.x = x;
        this->pos.y = y;
    }
    void setIsAte(bool isAte) { this->isAte = isAte; }
    void setIsKing(bool isKing) { this->isKing = isKing; }

    int getId() { return id; }
    Position getPos() { return pos; }
    bool getIsAte() { return isAte; }
    bool getIsKing() { return isKing; }
    virtual bool canMove(Position target, bool isTop) { return false; };
};

#endif