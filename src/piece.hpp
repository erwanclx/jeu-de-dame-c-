#ifndef PIECE_HPP
#define PIECE_HPP

#include "position.hpp"
#include "damier.hpp"
#include <iostream>
using namespace std;

class Piece
{
private:
    int id;
    Position pos;
    bool isAte;
    bool isKing;

protected:
    Damier *damier;

public:
    void setId(int id) { this->id = id; }
    void setDamier(Damier *damier) { this->damier = damier; }
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
    virtual bool canMove(Position target, bool isTop, Piece *pieces[12]) { return false; };
};

#endif