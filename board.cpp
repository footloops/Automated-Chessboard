#include "HardwareSerial.h"
#include "board.h"
#include <Arduino.h>

// Inital Board setup. Go through square and assign it it's inital piece.

char layOut_white[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
char layOut_black[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
board::board(){
  for (unsigned int column = 0; column < 8; column++)
  {
    // Black
    this->currentBoard[0][column] = new chessPiece(layOut_white[column], false, 1, letters[column], 'B');
    this->currentBoard[1][column] = new chessPiece('p', false, 2, letters[column], 'B');

    this->previousBoard[0][column] = new chessPiece(layOut_white[column], false, 1, letters[column], 'B');
    this->previousBoard[1][column] = new chessPiece('p', false, 2, letters[column], 'B');

    // White
    this->currentBoard[6][column] = new chessPiece('P', false, 7, letters[column], 'W');
    this->currentBoard[7][column] = new chessPiece(layOut_black[column], false, 8, letters[column], 'W');

    this->previousBoard[6][column] = new chessPiece('P', false, 7, letters[column], 'W');
    this->previousBoard[7][column] = new chessPiece(layOut_black[column], false, 8, letters[column], 'W');
  }

  for (unsigned int row = 2; row < 6; row++)
  {
    for(unsigned int column = 0; column < 8; column++)
    {
     this->currentBoard[row][column] = nullptr;
     this->previousBoard[row][column] = nullptr;
    }
  }

  return;
}

chessPiece* board::getTile(int row, int col){
  return this->currentBoard[row][col];
}

board::~board(){
  for (unsigned int row = 0; row < 8; row++){
    for (unsigned int column = 0; column < 8; row++){
      delete currentBoard[row][column];
      delete previousBoard[row][column];
      currentBoard[row][column] = nullptr;
      previousBoard[row][column] = nullptr;
    }
  }
  return;
}

void board::printBoard()
{
  for(unsigned int row = 0; row < 8; row++){
    for(unsigned int column = 0; column < 8; column++){
      if (currentBoard[row][column] != nullptr){
        Serial.print(this->currentBoard[row][column]->getPiece());
      }else{
        Serial.print(".");
      }
      Serial.print(" ");
    }
    Serial.println("");
  }

  return;
}