#ifndef KING_PIECE_HPP
#define KING_PIECE_HPP

#include "piece.hpp"
#include <iostream>
using namespace std;

class kingPiece : public Piece
{
public:
    kingPiece()
    {
        setIsKing(true);
    }

    bool canMove(Position target, bool isTop)
    {
        int deltaX = abs(target.x - getPos().x);
        int deltaY = abs(target.y - getPos().y);

        if (deltaX == deltaY)
        {
            if (target.x >= 0 && target.x < 8 && target.y >= 0 && target.y < 8)
            {
                return true;
            }
        }
        return false;
    };
};

#endif