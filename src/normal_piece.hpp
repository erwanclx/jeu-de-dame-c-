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

    bool canMove(Position target, bool isTop, Piece *pieces[12]) override
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
        else if (deltaX == 2 && deltaY == 2)
        {
            int middleX = (getPos().x + target.x) / 2;
            int middleY = (getPos().y + target.y) / 2;

            for (int i = 0; i < 12; i++)
            {
                if (pieces[i]->getPos().x == middleX && pieces[i]->getPos().y == middleY)
                {
                    Piece *capturedPiece = pieces[i];
                    if (!capturedPiece->getIsAte())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            return false;
        }
        return false;
    };
};

#endif