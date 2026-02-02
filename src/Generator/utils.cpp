// src/Generator/utils.cpp

#include "Generator.h"
#include "../Validator/Validator.h"

#include <vector>
#include <random>

std::mt19937 Generator::createRandomNumberGenerator() {
    std::random_device dev;
    return std::mt19937(dev());
}

void Generator::findNextEmpty(const Board& board, int& next_row, int& next_col) {
    int rows = board.getRows();
    int cols = board.getCols();

    // Iterate Through Board & Find Indices Of Next Empty Cell
    for (int row_idx = 0; row_idx < rows; row_idx++) {
        for (int col_idx = 0; col_idx < cols; col_idx++) {
            if (board.getCell(row_idx, col_idx) == 0) {
                next_row = row_idx;
                next_col = col_idx;
                return;
            }
        }
    }
}

void Generator::uniqueBoard(Board& board, int& count) {
    // Passed In: Current State Of Board, counter for solutions
    // Pass In By Reference So State Carries Over During Recursion

    // Base Case: If Count > 1, Board Is Not Unique, Break Recursion & Return
    if (count > 1)
        return;

    int next_row = -1;
    int next_col = -1;

    findNextEmpty(board, next_row, next_col);

    // If No Next Cell, Board Is Solved
    if (next_row == -1) {
        count++;
        return;
    }

    // If Empty Cell, Iterate Through Possible Values
    std::vector<int> possibleValues = {1,2,3,4,5,6,7,8,9};
    
    for (int value : possibleValues) {
        board.setCell(next_row, next_col, value);
        
        // If Valid Placement, Continue Along Board Filled At Spot
        bool valid_position = Validator::isValidPosition(board, next_row, next_col);

        if (valid_position)
            uniqueBoard(board, count);

        // If Multiple Solutions Backtrack And Prune Early
        if (count > 1) {
            board.setCell(next_row, next_col, 0);
            return;
        }
    }

    // Backtrack If Necessary
    board.setCell(next_row, next_col, 0);
    return;
}
