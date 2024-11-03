#ifndef CASE_HPP
#define CASE_HPP

#include "position.hpp"
#include <iostream>

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

#endif