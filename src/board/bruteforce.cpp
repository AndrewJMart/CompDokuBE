#include "board.h"

void Board::uniqueBoard(std::vector<std::vector<int>>& board, int& count) {
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
        board[next_row][next_col] = value;
        
        // If Valid Placement, Continue Along Board Filled At Spot
        if (isValidPosition(board, next_row, next_col))
            uniqueBoard(board, count);
        
        // If Multiple Solutions Backtrack And Prune Early
        if (count > 1)
            board[next_row][next_col] = 0;
            return;
    }

    // Backtrack If Necessary
    board[next_row][next_col] = 0;
    return;
};

void Board::findNextEmpty(std::vector<std::vector<int>>& board, int& next_row, int& next_col) {
    // Iterate Through Board & Find Indices Of Next Empty Cell
    for (int row_idx = 0; row_idx < rows; row_idx++) {
        for (int col_idx = 0; col_idx < cols; col_idx++) {
            if (board[row_idx][col_idx] == 0) {
                next_row = row_idx;
                next_col = col_idx;
                return;
            }
        }
    }
}
