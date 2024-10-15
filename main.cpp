//#include <iostream>
//using namespace std;
//
//
//int main() {
//  int row, col;
//  row = 5;
//  col = 5;
//
//  int table2d[row][col];
//
//  for (int i = 0; i < row; i++) {
//    for (int j = 0; j < col; j++) {
//      table2d[i][j] = 0;
//    }
//   }
//
//  for (int i = 0; i < row; i++) {
//    cout << "-  ";
//  }
//  for (int i = 0; i < row; i++) {
//    cout << endl;
//    for (int j = 0; j < col; j++) {
//      if (j == 0) {
//        cout << "| " << table2d[i][j] << " ";
//      }
//      else if (j == col - 1) {
//        cout << table2d[i][j] << " |";
//       }
//       else {
//         cout << "" << table2d[i][j] << " ";
//         }
//
//    }
//  }
//  cout << endl;
//  for (int i = 0; i < row; i++) {
//    cout << "-  ";
//  }
//
//
//}

#include <iostream>
#include <list>
using namespace std;

struct Position
{
    int x;
    int y;
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
    int row = 10;
    int col = 10;
    char board[10][10];

  public:

    void colorBoard()
    {
      for (int i = 0; i < row; i++)
      {
        for (int j = 0; j < col; j++)
        {
          if (j % 2 == 0 && i % 2 == 0)
            {
              board[i][j] = '*';
            }
          else if (j % 2 == 1 && i % 2 == 1)
            {
              board[i][j] = '*';
            }
          else {
              board[i][j] = '_';
            }
        }
      }
    };
    void printBoard()
    {
      cout << string(this->col*5,'=') << endl;
      for (int i = 0; i < row; i++)
      {
        for (int j = 0; j < col; j++)
          {
          if (j % 2 == 0 && i % 2 == 0)
          {
            cout << "| \033[1;34m" << board[i][j] << "\033[0m |";
          }
          else if (j % 2 == 1 && i % 2 == 1)
          {
            cout << "| \033[1;34m" << board[i][j] << "\033[0m |";
          }
          else {
            cout << "| \033[1;31m" << board[i][j] << "\033[0m |";
          }
          if (j == col - 1)
            {
            cout << endl;
            }
          }
        cout << string(this->col*5,'=') << endl;
       }

     }
};

int main() {
  Damier damier;
  damier.colorBoard();
  damier.printBoard();
}