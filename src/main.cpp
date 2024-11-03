#include <iostream>
#include <list>

#include "color.hpp"
#include "game.hpp"

using namespace std;

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