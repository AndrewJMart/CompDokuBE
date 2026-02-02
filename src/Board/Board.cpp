// src/Board/Board.cpp

#include "Board.h"

Board::Board(int row, int col): 
    cols(col), rows(row),
    board(rows, std::vector<int>(cols)) {
}

int Board::getCols() const {
    return cols;
}

int Board::getRows() const {
    return rows;
}

int Board::getCell(int row, int col) const {
    return board[row][col];
}

void Board::setCell(int row, int col, int value) {
    board[row][col] = value;
}