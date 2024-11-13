#ifndef GAME_HPP
#define GAME_HPP

#include "piece.hpp"
#include "player.hpp"
#include <iostream>
using namespace std;

class Game
{
private:
    Player player1;
    Player player2;
    Damier damier;

    void displayRemainingPieces(Player &player)
    {
        cout << player.getBgColor() << player.getName() << " : " << palette.reset;
        Piece **pieces = player.getPieces();
        for (int i = 0; i < 12; i++)
        {
            if (!pieces[i]->getIsAte())
            {
                cout << player.getBgColor() << " " << pieces[i]->getId() << " " << palette.reset;
            }
        }
        cout << endl;
    }

public:
    bool round(Player &currentPlayer, Player &opponent)
    {
        string color = currentPlayer.getColor();
        string bgColor = currentPlayer.getBgColor();

        damier.printBoard();

        displayRemainingPieces(player1);
        cout << player1.getColor() << "🎯 Score: " << player1.getScore() << palette.reset << endl
             << endl;

        displayRemainingPieces(player2);
        cout << player2.getColor() << "🎯 Score: " << player2.getScore() << palette.reset << endl;

        cout << palette.yellow << "\n \n C'est à " << currentPlayer.getName() << " de jouer !" << palette.reset << endl;

        int id, x, y;
        cout << color << " Entrez l'id de la pièce à déplacer" << palette.reset << endl;
        cin >> id;
        cout << color << " Entrez la ligne cible : " << palette.reset << endl;
        cin >> x;
        cout << color << " Entrez la colonne cible :" << palette.reset << endl;
        cin >> y;

        while (!currentPlayer.movePiece(id, x, y, damier, opponent))
        {
            cout << color << " Entrez l'id de la pièce à déplacer" << palette.reset << endl;
            cin >> id;
            cout << color << " Entrez la ligne cible : " << palette.reset << endl;
            cin >> x;
            cout << color << " Entrez la colonne cible :" << palette.reset << endl;
            cin >> y;
        }
        return true;
    }

    void start(string name1, string name2)
    {
        player1.setColor(palette.black);
        player1.setBgColor(palette.bgRed);
        player1.setName(name1);
        player1.setIsTop(true);

        player2.setColor(palette.black);
        player2.setBgColor(palette.bgGreen);
        player2.setName(name2);
        player2.setIsTop(false);

        player1.initPieces(&damier);
        player2.initPieces(&damier);
        damier.initBoard();

        Piece **pieces1 = player1.getPieces();
        for (int i = 0; i < 12; i++)
        {
            damier.putPiece(pieces1[i]->getPos().x, pieces1[i]->getPos().y,
                            player1.getPieceSymbol(pieces1[i]->getId()));
        }

        Piece **pieces2 = player2.getPieces();
        for (int i = 0; i < 12; i++)
        {
            damier.putPiece(pieces2[i]->getPos().x, pieces2[i]->getPos().y,
                            player2.getPieceSymbol(pieces2[i]->getId()));
        }

        damier.printBoard();

        while (true)
        {
            if (round(player1, player2))
            {
                if (player1.getScore() >= 12)
                {
                    displayRemainingPieces(player1);
                    displayRemainingPieces(player2);
                    cout << palette.magenta << player1.getName() << " a gagné 🎉" << palette.reset << endl;
                    break;
                }
                damier.printBoard();
            }
            if (round(player2, player1))
            {
                if (player2.getScore() >= 12)
                {
                    displayRemainingPieces(player1);
                    displayRemainingPieces(player2);
                    cout << palette.magenta << player2.getName() << " a gagné 🎉" << palette.reset << endl;
                    break;
                }

                damier.printBoard();
            }
        }
    }
};

#endif