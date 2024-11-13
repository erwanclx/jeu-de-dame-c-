#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "normal_piece.hpp"
#include "king_piece.hpp"
#include "damier.hpp"
#include "color.hpp"
#include <iostream>
using namespace std;

class Player
{
private:
    string name;
    string color;
    string bgColor;
    Piece *pieces[12];
    bool isTop;
    int score = 0;

public:
    Player()
    {
        for (int i = 0; i < 12; i++)
        {
            pieces[i] = new kingPiece();
            // pieces[i] = new NormalPiece();
        }
    }

    ~Player()
    {
        for (int i = 0; i < 12; i++)
        {
            delete pieces[i];
        }
    }

    void setName(string name) { this->name = name; }
    void setColor(string color) { this->color = color; }
    void setBgColor(string bgColor) { this->bgColor = bgColor; }
    void setIsTop(bool isTop) { this->isTop = isTop; }
    void incrementScore() { score++; }

    string getName() { return name; }
    bool getIsTop() { return isTop; }
    string getColor() { return color; }
    string getBgColor() { return bgColor; }
    int getScore() { return score; }

    Piece **getPieces() { return pieces; }

    string getPieceSymbol(int id)
    {
        if (pieces[id - 1]->getIsKing())
        {
            color = palette.yellow;
        }

        if (id > 9)
        {
            return color + bgColor + " " + to_string(id) + palette.reset;
        }
        else
        {
            return color + bgColor + "  " + to_string(id) + palette.reset;
        }
    }

    void initPieces(Damier *damier)
    {
        int index = 0;
        int startRow = isTop ? 0 : 5;
        int endRow = isTop ? 3 : 8;

        for (int i = startRow; i < endRow; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
                {
                    pieces[index]->setId(index + 1);
                    pieces[index]->setDamier(damier);
                    pieces[index]->setPos(i, j);
                    pieces[index]->setIsAte(false);
                    index++;
                }
            }
        }
    }

    void previewMovement(int x, int y, Damier &damier)
    {
        Case &targetCase = damier.getCase(x, y);
        string originalColor = targetCase.getCaseColor();
        targetCase.setCaseColor(palette.bgMagenta + "   " + palette.reset);
        cout << palette.yellow << "Voulez-vous valider ?" << palette.reset << endl;
        damier.printBoard();
    }

    Piece *findPieceAtPosition(int x, int y)
    {
        for (int i = 0; i < 12; i++)
        {
            if (!pieces[i]->getIsAte() && pieces[i]->getPos().x == x && pieces[i]->getPos().y == y)
            {
                return pieces[i];
            }
        }
        return nullptr;
    }

    bool movePiece(int id, int x, int y, Damier &damier, Player &opponent)
    {
        for (int i = 0; i < 12; i++)
        {
            if (pieces[i]->getId() == id && !pieces[i]->getIsAte())
            {
                if (x >= 0 && x < 8 && y >= 0 && y < 8)
                {
                    Position target;
                    target.x = x;
                    target.y = y;

                    if (pieces[i]->canMove(target, isTop, opponent.getPieces()) && !damier.getCase(x, y).getIsOccuped())
                    {
                        previewMovement(x, y, damier);

                        string confirm;
                        cout << palette.green << "Confirmer ? (1: Oui, 0: Non)" << palette.reset << endl;
                        cin >> confirm;
                        if (confirm != "1")
                        {
                            damier.getCase(x, y).setCaseColor(palette.bgWhite + "   " + palette.reset);
                            damier.printBoard();
                            cout << "false";
                            return false;
                        }
                        else
                        {
                            int deltaX = abs(target.x - pieces[i]->getPos().x);
                            int deltaY = abs(target.y - pieces[i]->getPos().y);

                            if (deltaX == 2 && deltaY == 2)
                            {
                                int middleX = (pieces[i]->getPos().x + x) / 2;
                                int middleY = (pieces[i]->getPos().y + y) / 2;
                                opponent.findPieceAtPosition(middleX, middleY)->setIsAte(true);
                                damier.removePiece(middleX, middleY);
                                incrementScore();
                                cout << palette.green << "Capture réussie! Score: " << score << palette.reset << endl;
                            }

                            damier.removePiece(pieces[i]->getPos().x, pieces[i]->getPos().y);
                            damier.putPiece(x, y, getPieceSymbol(id));
                            pieces[i]->setPos(x, y);
                            cout << palette.yellow << pieces[i]->getPos().x << "   " << pieces[i]->getPos().y << palette.reset << endl;
                            cout << palette.green << "Coup joué ->" << palette.reset << endl;

                            if (isTop && x == 7)
                            {
                                int kingId = pieces[i]->getId();
                                Position pos = pieces[i]->getPos();
                                delete pieces[i];
                                pieces[i] = new kingPiece();
                                pieces[i]->setId(kingId);
                                pieces[i]->setPos(pos.x, pos.y);
                            }
                            else if (!isTop && x == 0)
                            {
                                int kingId = pieces[i]->getId();
                                Position pos = pieces[i]->getPos();
                                delete pieces[i];
                                pieces[i] = new kingPiece();
                                pieces[i]->setId(kingId);
                                pieces[i]->setPos(pos.x, pos.y);
                            }

                            damier.printBoard();
                            return true;
                        }
                    }
                    else
                    {
                        cout << palette.red << "Mouvement invalide" << endl;
                        return false;
                    }
                }
            }
        }
        cout << palette.red << "Pièce non trouvée ou déjà mangée" << palette.reset << endl;
        return false;
    }
};

#endif