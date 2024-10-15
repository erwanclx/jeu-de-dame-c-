#include <iostream>
#include <list>
using namespace std;

struct Position
{
  int x;
  int y;
};

struct Piece
{
  int id;
  Position pos;
};

class Player
{
private:
  string name;
  string pieceSymbol;
  Piece pieces[12];
  bool isTop;

public:
  void setName(string name)
  {
    this->name = name;
  }
  void setPieceSymbol(string pieceSymbol)
  {
    this->pieceSymbol = pieceSymbol;
  };
  void setIsTop(bool isTop)
  {
    this->isTop = isTop;
  }
  void initPieces()
  {

    int index = 0;

    if (isTop)
    {
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
          {
            pieces[index].id = index + 1;
            pieces[index].pos.x = i;
            pieces[index].pos.y = j;
            index++;
          }
        }
      }
    }
    else
    {
      for (int i = 5; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
          {
            pieces[index].id = index + 1;
            pieces[index].pos.x = i;
            pieces[index].pos.y = j;
            index++;
          }
        }
      }
    }
  };

  string getPieceSymbol()
  {
    return pieceSymbol;
  };
  string getName()
  {
    return name;
  }
  bool getIsTop()
  {
    return isTop;
  }
  void printPieces()
  {
    for (int i = 0; i < 12; i++)
    {
      cout << pieces[i].id;
    }
  }
  Piece (&getPieces())[12]
  {
    return pieces;
  }

  void initPieces()
  {

    int index = 0;

    if (isTop)
    {
      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
          {
            pieces[index].id = index + 1;
            pieces[index].pos.x = i;
            pieces[index].pos.y = j;
            index++;
          }
        }
      }
    }
    else
    {
      for (int i = 5; i < 8; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          if ((i % 2 == 0 && j % 2 == 1) || (i % 2 == 1 && j % 2 == 0))
          {
            pieces[index].id = index + 1;
            pieces[index].pos.x = i;
            pieces[index].pos.y = j;
            index++;
          }
        }
      }
    }
  };
};

class Case
{
private:
  Position pos;
  bool isOccuped;
  string caseColor;
  string pieceColor;

public:
  void setPos(int x, int y)
  {
    this->pos.x = x;
    this->pos.y = y;
  };
  void setIsOccuped(bool isOccuped)
  {
    this->isOccuped = isOccuped;
  };
  void setCaseColor(string pieceColor)
  {
    this->pieceColor = pieceColor;
  };
  void setPieceColor(string pieceColor)
  {
    this->pieceColor = pieceColor;
  };

  Position getPos()
  {
    return pos;
  };
  bool getIsOccuped()
  {
    return isOccuped;
  };
  string getCaseColor()
  {
    return pieceColor;
  };
  string getPieceColor()
  {
    return pieceColor;
  };
};

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
        if (j % 2 == 0 && i % 2 == 0)
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor("*");
          board[i][j] = newCase;
        }
        else if (j % 2 == 1 && i % 2 == 1)
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor("*");
          board[i][j] = newCase;
        }
        else
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor("_");
          board[i][j] = newCase;
        }
      }
    }
  };
  void printBoard()
  {
    cout << string(this->col * 5, '=') << endl;
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        if (j % 2 == 0 && i % 2 == 0)
        {
          cout << "| \033[1;34m" << board[i][j].getCaseColor() << "\033[0m |";
        }
        else if (j % 2 == 1 && i % 2 == 1)
        {
          cout << "| \033[1;34m" << board[i][j].getCaseColor() << "\033[0m |";
        }
        else
        {
          cout << "| \033[1;31m" << board[i][j].getCaseColor() << "\033[0m |";
        }
        if (j == col - 1)
        {
          cout << endl;
        }
      }
      cout << string(this->col * 5, '=') << endl;
    }
  }

  void putPiece(int x, int y, string c)
  {
    board[x][y].setIsOccuped(true);
    board[x][y].setCaseColor(c);
  }
};

int main()
{
  Player player1;
  Player player2;

  player1.setPieceSymbol("1");
  player1.setName("Erwan");
  player1.setIsTop(true);

  player2.setPieceSymbol("2");
  player2.setName("Joker");

  player1.initPieces();
  player2.initPieces();

  string piecePlayer1 = player1.getPieceSymbol();
  string piecePlayer2 = player2.getPieceSymbol();

  Damier damier;
  damier.initBoard();
  damier.printBoard();

  cout << endl;

  Piece(&piecesPlayer1)[12] = player1.getPieces();
  Piece(&piecesPlayer2)[12] = player2.getPieces();

  for (int i = 0; i < 12; i++)
  {
    // cout << "Erwan Position :" << piecesPlayer1[i].pos.x << "," << piecesPlayer1[i].pos.y << endl;
    damier.putPiece(piecesPlayer1[i].pos.x, piecesPlayer1[i].pos.y, piecePlayer1);
  }

  for (int i = 0; i < 12; i++)
  {
    // cout << "Joker Position :" << piecesPlayer2[i].pos.x << "," << piecesPlayer2[i].pos.y << endl;
    damier.putPiece(piecesPlayer2[i].pos.x, piecesPlayer2[i].pos.y, piecePlayer2);
  }

  cout << "\n\n\n\n\n\n\n";

  damier.printBoard();
}