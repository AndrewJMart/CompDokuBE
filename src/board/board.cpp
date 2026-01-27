#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

#include "board.h"

bool Board::fillBoard(int row, int col, std::mt19937& rng) {
    // Base Case: If Board Full & isValid Board Solved
    if (row == rows)
        return true;

    // At This Point, Board Is Valid
    // Try Different Values And Test Validitity
    std::vector<int> sudoku_values = {1,2,3,4,5,6,7,8,9};
    shuffle(sudoku_values.begin(), sudoku_values.end(), rng);

    // Loop Through Shuffled Possible Values
    for (int value : sudoku_values) {
        board[row][col] = value;

        int next_row = row;
        int next_col = col;

        // If Assigned Value Is Valid, Call Fill Board With Next Cell
        if (isValidPosition(board, row, col)) {
            // If At End Of Row, Increment Row & Reset Column
            if ( (col + 1) == cols ) {
                next_row++;
                next_col = 0;
            }
            else {
                next_col++;
            }

            if (fillBoard(next_row, next_col, rng))
                return true;
        }
    }
    // If Valid Value Not Possible. Backtrack
    board[row][col] = 0;
    return false;
}

void Board::generateBoard() {
    std::random_device dev;
    std::mt19937 rng(dev());

    fillBoard(0, 0, rng);
}

bool Board::isValidPosition(std::vector<std::vector<int>>& board, int row, int col) {
    int posValue = board[row][col];

    // Check If Valid Along Rows
    for (int col_check = 0; col_check < cols; col_check++){
        if (col == col_check)
            continue;
        
        if (posValue == board[row][col_check])
            return false;
    }

    // Check If Valid Along Cols
    for (int row_check = 0; row_check < rows; row_check++){
            if (row == row_check)
                continue;

            if (posValue == board[row_check][col])
                return false;
    }

    // Check If Valid Within SubMatrix
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;

    for (int row_idx = row_start; row_idx < (row_start + 3); row_idx++){
        for (int col_idx = col_start; col_idx < (col_start + 3); col_idx ++){
            if (row_idx == row && col_idx == col)
                continue;

            if (posValue == board[row_idx][col_idx])
                return false;
        }
    }
    return true;
}

bool Board::isValid() {
    // Create Vectors To Store Bit Representations
    std::vector<int> rowchecker(rows);
    std::vector<int> colchecker(cols);
    std::vector<int> matrixchecker(9);

    // Loop Through All Values
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // If Empty Continue
            if (board[row][col] == 0)
                return false;
            
            // Position Value In Bitmask
            int pos = 1 << (board[row][col] - 1);

            // Check If Exists In Row
            if (rowchecker[row] & pos)
                return false;

            // Check if Exists In Column
            if (colchecker[col] & pos)
                return false;

            // Check If Value Exists In Matrix
            int row_location = row / 3;
            int col_location = col / 3;
            int matrix_value = (row_location * 3) + col_location;

            if (matrixchecker[matrix_value] & pos)
                return false;

            // Mark Value As Seen
            rowchecker[row] |= pos;
            colchecker[col] |= pos;
            matrixchecker[matrix_value] |= pos;
        }
    }
    return true;
}

Board::Board(): 
    rows(9), cols(9), 
    board(rows, std::vector<int>(cols)), 
    solveboard(rows, std::vector<int>(cols))
    {
        generateBoard();
        solveboard = board;
    }

void Board::printBoard() {
    // Loop Through Rows
    for (int row = 0; row < rows; row ++) {
        // Loop Through Columns
        for (int col = 0; col < cols; col++) {
            std::cout << board[row][col] << " | ";
        }
        std::cout << std::endl;
    }
}
