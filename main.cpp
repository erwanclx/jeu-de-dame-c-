#include <iostream>
#include <list>
using namespace std;

struct Color
{
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
Color palette;

struct Position
{
  int x;
  int y;
};

struct Piece
{
  int id;
  Position pos;
  bool isAte = false;
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
  }
  void setIsOccuped(bool isOccuped) { this->isOccuped = isOccuped; }
  void setCaseColor(string caseColor) { this->caseColor = caseColor; }
  void setPieceColor(string pieceColor) { this->pieceColor = pieceColor; }

  Position getPos() { return pos; }
  bool getIsOccuped() { return isOccuped; }
  string getCaseColor() { return caseColor; }
  string getPieceColor() { return pieceColor; }
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

class Player
{
private:
  string name;
  string color;
  string bgColor;
  Piece pieces[12];
  bool isTop;
  int score = 0;

public:
  Player()
  {
    for (int i = 0; i < 12; i++)
    {
      pieces[i].isAte = false;
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

  Piece *getPieces() { return pieces; }

  string getPieceSymbol(int id)
  {
    if (id > 9)
    {
      return color + bgColor + " " + to_string(id) + palette.reset;
    }
    else
    {
      return color + bgColor + "  " + to_string(id) + palette.reset;
    }
  }

  void initPieces()
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
          pieces[index].id = index + 1;
          pieces[index].pos.x = i;
          pieces[index].pos.y = j;
          pieces[index].isAte = false;
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
      if (!pieces[i].isAte && pieces[i].pos.x == x && pieces[i].pos.y == y)
      {
        return &pieces[i];
      }
    }
    return nullptr;
  }

  bool movePiece(int id, int x, int y, Damier &damier, Player &opponent)
  {
    for (int i = 0; i < 12; i++)
    {
      if (pieces[i].id == id && !pieces[i].isAte)
      {
        int currentX = pieces[i].pos.x;
        int currentY = pieces[i].pos.y;

        if (x >= 0 && x < 8 && y >= 0 && y < 8)
        {
          int deltaX = abs(x - currentX);
          int deltaY = abs(y - currentY);

          if (deltaX == 1 && deltaY == 1)
          {
            if ((isTop && x > currentX) || (!isTop && x < currentX))
            {
              if (!damier.getCase(x, y).getIsOccuped())
              {
                previewMovement(x, y, damier);

                string confirm;
                cout << palette.green << "Confirmer ? (1: Oui, 0: Non)" << palette.reset << endl;
                cin >> confirm;
                if (confirm != "1")
                {
                  damier.getCase(x, y).setCaseColor(palette.bgWhite + "   " + palette.reset);
                  damier.printBoard();
                  return false;
                }

                damier.removePiece(currentX, currentY);
                damier.putPiece(x, y, getPieceSymbol(id));
                pieces[i].pos.x = x;
                pieces[i].pos.y = y;

                cout << palette.green << "Coup joué ->" << palette.reset << endl;
                damier.printBoard();
                return true;
              }
            }
            else
            {
              cout << palette.red << "Mouvement dans la mauvaise direction" << palette.reset << endl;
              return false;
            }
          }

          else if (deltaX == 2 && deltaY == 2)
          {
            int middleX = (currentX + x) / 2;
            int middleY = (currentY + y) / 2;

            Piece *capturedPiece = opponent.findPieceAtPosition(middleX, middleY);
            if (capturedPiece && !damier.getCase(x, y).getIsOccuped())
            {
              previewMovement(x, y, damier);

              string confirm;
              cout << palette.green << "Confirmer la capture ? (1: Oui, 0: Non)" << palette.reset << endl;
              cin >> confirm;
              if (confirm != "1")
              {
                damier.getCase(x, y).setCaseColor(palette.bgWhite + "   " + palette.reset);
                damier.printBoard();
                return false;
              }

              capturedPiece->isAte = true;
              damier.removePiece(middleX, middleY);

              damier.removePiece(currentX, currentY);
              damier.putPiece(x, y, getPieceSymbol(id));
              pieces[i].pos.x = x;
              pieces[i].pos.y = y;

              incrementScore();

              cout << palette.green << "Capture réussie! Score: " << score << palette.reset << endl;
              damier.printBoard();
              return true;
            }
          }
        }

        cout << palette.red << "Position invalide. Veuillez réessayer" << palette.reset << endl;
        return false;
      }
    }
    cout << palette.red << "Pièce non trouvée ou déjà mangée" << palette.reset << endl;
    return false;
  }
};

class Game
{
private:
  Player player1;
  Player player2;
  Damier damier;

  void displayRemainingPieces(Player &player)
  {
    cout << player.getBgColor() << player.getName() << " : " << palette.reset;
    Piece *pieces = player.getPieces();
    for (int i = 0; i < 12; i++)
    {
      if (!pieces[i].isAte)
      {
        cout << player.getBgColor() << " " << pieces[i].id << " " << palette.reset;
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

    player1.initPieces();
    player2.initPieces();
    damier.initBoard();

    Piece *pieces1 = player1.getPieces();
    for (int i = 0; i < 12; i++)
    {
      damier.putPiece(pieces1[i].pos.x, pieces1[i].pos.y,
                      player1.getPieceSymbol(pieces1[i].id));
    }

    Piece *pieces2 = player2.getPieces();
    for (int i = 0; i < 12; i++)
    {
      damier.putPiece(pieces2[i].pos.x, pieces2[i].pos.y,
                      player2.getPieceSymbol(pieces2[i].id));
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
int main()
{
  string name1, name2;
  cout << palette.green << "Bienvenue dans le jeu de dames" << palette.reset << endl;
  cout << palette.green << "================================" << palette.reset << endl;
  cout << palette.red << "Joueur 1, veuillez entrer votre nom" << palette.reset << endl;
  cin >> name1;
  cout << palette.green << "Joueur 2, veuillez entrer votre nom" << palette.reset << endl;
  cin >> name2;

  Game game;
  game.start(name1, name2);
  return 0;
}