#include <iostream>
#include <list>
using namespace std;

struct Color
{
  // https://en.wikipedia.org/wiki/ANSI_escape_code
  string reset = "\033[0m";
  string black = "\033[1;30m";
  string red = "\033[1;31m";
  string green = "\033[1;32m";
  string yellow = "\033[1;33m";
  string blue = "\033[1;34m";
  string magenta = "\033[1;35m";
  string cyan = "\033[1;36m";
  string white = "\033[1;37m";

  string bgBlack = "\033[1;40m";
  string bgRed = "\033[1;41m";
  string bgGreen = "\033[1;42m";
  string bgYellow = "\033[1;43m";
  string bgBlue = "\033[1;44m";
  string bgMagenta = "\033[1;45m";
  string bgCyan = "\033[1;46m";
  string bgWhite = "\033[1;47m";
};

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
    Color palette;
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        if (j % 2 == 0 && i % 2 == 0)
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor(palette.bgBlack + "   " + palette.reset);
          board[i][j] = newCase;
        }
        else if (j % 2 == 1 && i % 2 == 1)
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor(palette.bgBlack + "   " + palette.reset);
          board[i][j] = newCase;
        }
        else
        {
          Case newCase;
          newCase.setPos(i, j);
          newCase.setIsOccuped(false);
          newCase.setCaseColor(palette.bgWhite + "   " + palette.reset);
          board[i][j] = newCase;
        }
      }
    }
  };
  void printBoard()
  {
    for (int i = 0; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        cout << board[i][j].getCaseColor();
        if (j == col - 1)
        {
          cout << endl;
        }
      }
    }
  }
  Case &getCase(int x, int y)
  {
    return board[x][y];
  }

  void putPiece(int x, int y, string c)
  {
    board[x][y].setIsOccuped(true);
    board[x][y].setCaseColor(c);
  }
  void removePiece(int x, int y)
  {
    Color palette;
    board[x][y].setIsOccuped(false);
    if (x % 2 == 0 && y % 2 == 0)
    {
      board[x][y].setCaseColor(palette.bgBlack + "   " + palette.reset);
    }
    else if (x % 2 == 1 && y % 2 == 1)
    {
      board[x][y].setCaseColor(palette.bgBlack + "   " + palette.reset);
    }
    else
    {
      board[x][y].setCaseColor(palette.bgWhite + "   " + palette.reset);
    }
  }
};

class Player
{
private:
  string name;
  string pieceSymbol;
  string color;
  string bgColor;
  Piece pieces[12];
  bool isTop;

public:
  void setName(string name)
  {
    this->name = name;
  };
  void setPieceSymbol(string pieceSymbol)
  {
    this->pieceSymbol = pieceSymbol;
  };
  void setColor(string color)
  {
    this->color = color;
  };
  void setBgColor(string bgColor)
  {
    this->bgColor = bgColor;
  };
  void setIsTop(bool isTop)
  {
    this->isTop = isTop;
  };

  string getPieceSymbol()
  {
    Color palette;
    return color + bgColor + " " + pieceSymbol + " " + palette.reset;
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
  bool movePiece(int id, int x, int y, Damier &damier)
  {
    for (int i = 0; i < 12; i++)
    {
      if (pieces[i].id == id)
      {
        int currentX = pieces[i].pos.x;
        int currentY = pieces[i].pos.y;

        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
          if (!damier.getCase(x, y).getIsOccuped())
          {
            damier.removePiece(currentX, currentY);
            damier.putPiece(x, y, getPieceSymbol());
            return true;
          }
          else
          {
            cout << "Impossible de bouger la piece" << endl;
            return false;
          }
        }
      }
    }
  };
};

int main()
{

  Player player1;
  Player player2;

  Color color;

  player1.setColor(color.black);
  player1.setBgColor(color.bgRed);
  player1.setPieceSymbol("1");
  player1.setName("Erwan");
  player1.setIsTop(true);

  player2.setColor(color.black);
  player2.setBgColor(color.bgGreen);
  player2.setPieceSymbol("2");
  player2.setName("Joker");
  player2.setIsTop(false);

  player1.initPieces();
  player2.initPieces();

  string piecePlayer1 = player1.getPieceSymbol();
  string piecePlayer2 = player2.getPieceSymbol();

  cout << "Player 1 : " << player1.getName() << endl;
  cout << "Player 1 symbol : " << player1.getPieceSymbol() << endl;

  cout << "Player 2 : " << player2.getName() << endl;
  cout << "Player 2 symbol : " << player2.getPieceSymbol() << endl;

  Damier damier;
  damier.initBoard();

  damier.printBoard();
  cout << endl;

  Piece(&piecesPlayer1)[12] = player1.getPieces();
  Piece(&piecesPlayer2)[12] = player2.getPieces();

  for (int i = 0; i < 12; i++)
  {
    damier.putPiece(piecesPlayer1[i].pos.x, piecesPlayer1[i].pos.y, piecePlayer1);
  }

  for (int i = 0; i < 12; i++)
  {
    damier.putPiece(piecesPlayer2[i].pos.x, piecesPlayer2[i].pos.y, piecePlayer2);
  }

  damier.printBoard();
  cout << endl;

  player1.movePiece(1, 3, 4, damier);

  damier.printBoard();
  cout << endl;
}