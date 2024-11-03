#ifndef DAMIER_HPP
#define DAMIER_HPP

#include "case.hpp"
#include "color.hpp"
#include <iostream>
using namespace std;

class Damier
{
private:
    int row = 8;
    int col = 8;
    Case board[8][8];

public:
    void initBoard()
    {
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                Case newCase;
                newCase.setPos(i, j);
                newCase.setIsOccuped(false);

                if ((j % 2 == 0 && i % 2 == 0) || (j % 2 == 1 && i % 2 == 1))
                {
                    newCase.setCaseColor(palette.bgBlack + "   " + palette.reset);
                }
                else
                {
                    newCase.setCaseColor(palette.bgWhite + "   " + palette.reset);
                }

                board[i][j] = newCase;
            }
        }
    }

    void printBoard()
    {
        cout << "\033[H\033[2J\033[3J";
        for (int i = 0; i < col; i++)
            cout << "---";
        cout << endl;

        for (int i = 0; i < col; i++)
            cout << " " << i << " ";
        cout << endl;

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                cout << board[i][j].getCaseColor();
                if (j == col - 1)
                    cout << " " << i << endl;
            }
        }

        for (int i = 0; i < col; i++)
            cout << "---";
        cout << endl;
    }

    Case &getCase(int x, int y) { return board[x][y]; }

    void putPiece(int x, int y, string c)
    {
        board[x][y].setIsOccuped(true);
        board[x][y].setCaseColor(c);
    }

    void removePiece(int x, int y)
    {
        board[x][y].setIsOccuped(false);
        if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
        {
            board[x][y].setCaseColor(palette.bgBlack + "   " + palette.reset);
        }
        else
        {
            board[x][y].setCaseColor(palette.bgWhite + "   " + palette.reset);
        }
    }
};

#endif