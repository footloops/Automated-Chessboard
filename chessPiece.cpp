#include "chessPiece.h"

// Takes in colour, piece, and empty
chessPiece::chessPiece(char piece, bool empty, unsigned int row, char col, char colour)
{
  this->piece = piece;
  this->empty = empty;
  this->row = row;
  this->col = col; 
  this->colour = colour;
};

void chessPiece::setCol(char col){
  this->col = col;
  return;
}

void chessPiece::setRow(unsigned int row){
  this->row = row;
  return;
}

void chessPiece::setEmpty(bool empty){
  this->empty = empty;
  return;
}

void chessPiece::setColour(char colour){
  this->colour = colour;
  return;
}

unsigned int chessPiece::getRow(){
  return this->row;
}

char chessPiece::getCol(){
  return this->col;
}

char chessPiece::getPiece(){
  return this->piece;
}

bool chessPiece::isEmpty(){
  return this->empty;
}

char chessPiece::getColour(){
  return this->colour;
}