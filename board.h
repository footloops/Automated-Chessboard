#ifndef BOARD_H
#define BOARD_H

#include "chessPiece.h"

class board{

  public:
    board();
    ~board();

    void printBoard();
    chessPiece* getTile(int row, int col);

  private:
    chessPiece* currentBoard[8][8];
    chessPiece* previousBoard[8][8];
};

#endif