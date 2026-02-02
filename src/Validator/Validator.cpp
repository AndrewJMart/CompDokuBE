// src/Validator/Validator.cpp

#include "Validator.h"
#include <iostream>
#include <vector>

Validator::Validator() {}

bool Validator::isValidPosition(const Board& board, int row, int col) {
    int rows = board.getRows();
    int cols = board.getCols();

    int posValue = board.getCell(row, col);

    // Check If Valid Along Rows
    for (int col_check = 0; col_check < cols; col_check++){
        if (col == col_check)
            continue;
        
        if (posValue == board.getCell(row, col_check))
            return false;
    }

    // Check If Valid Along Cols
    for (int row_check = 0; row_check < rows; row_check++){
            if (row == row_check)
                continue;

            if (posValue == board.getCell(row_check, col))
                return false;
    }

    // Check If Valid Within SubMatrix
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;

    for (int row_idx = row_start; row_idx < (row_start + 3); row_idx++){
        for (int col_idx = col_start; col_idx < (col_start + 3); col_idx ++){
            if (row_idx == row && col_idx == col)
                continue;

            if (posValue == board.getCell(row_idx, col_idx))
                return false;
        }
    }
    return true;
}

bool Validator::isValid(const Board& board) {
    int rows = board.getRows();
    int cols = board.getCols();

    // Create Vectors To Store Bit Representations
    std::vector<int> rowchecker(rows);
    std::vector<int> colchecker(cols);
    std::vector<int> matrixchecker(rows);

    // Loop Through All Values
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int cellValue = board.getCell(row, col);
            // If Empty Continue
            if (cellValue == 0)
                return false;
            
            // Position Value In Bitmask
            int pos = 1 << (cellValue - 1);

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

void Validator::printBoard(const Board& printBoard) {
    int rows = printBoard.getRows();
    int cols = printBoard.getCols();

    // Loop Through Rows
    for (int row = 0; row < rows; row ++) {
        // Loop Through Columns
        for (int col = 0; col < cols; col++) {
            std::cout << printBoard.getCell(row, col) << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}