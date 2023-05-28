#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class chessPiece{
  public:
    chessPiece(char piece, bool empty, unsigned int row, char col, char colour);
    char getCol();
    unsigned int getRow();
    char getPiece();
    bool isEmpty();
    char getColour();

    void setRow(unsigned int row);
    void setCol(char col);
    void setPiece(char piece);
    void setEmpty(bool empty);
    void setColour(char colour);
  private:
    bool empty; // No piece on square
    char piece;
    unsigned int row;
    char col;
    char colour; // W - white, B - black, N - None
};


#endif