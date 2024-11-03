#ifndef NORMAL_PIECE_HPP
#define NORMAL_PIECE_HPP

#include "piece.hpp"
#include <iostream>
using namespace std;

class NormalPiece : public Piece
{
public:
    NormalPiece()
    {
        setIsKing(false);
    }

    bool canMove(Position target, bool isTop)
    {
        int deltaX = abs(target.x - getPos().x);
        int deltaY = abs(target.y - getPos().y);

        if (deltaX == 1 && deltaY == 1)
        {
            if ((isTop && target.x > getPos().x) || (!isTop && target.x < getPos().x))
            {
                if (target.x >= 0 && target.x < 8 && target.y >= 0 && target.y < 8)
                {
                    return true;
                }
            }
        }
        return false;
    };
};

#endif