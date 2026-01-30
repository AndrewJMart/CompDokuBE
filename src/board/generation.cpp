#include "board.h"

Board::Board(): 
    rows(9), cols(9), 
    board(rows, std::vector<int>(cols)), 
    solveboard(rows, std::vector<int>(cols))
    {
        generateBoard();
        solveboard = board;
    }

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
}

bool Board::logicalSolver(std::vector<std::vector<int>> board){
    // Given A Board, Iteratively Apply Human Solver Techniques Until Board
    // Is Solved Or Not

    // Create Candidate Set For Original Board
    std::vector<std::vector<int>> candidate_set(rows, std::vector<int>(cols, 0x1FF));
    createCandidateSet(board, candidate_set);

    // Return Case: If At End Of Progress, Board Is Solved, Return True
    if (isValid(board)) {
        return true;
    }
    else {
        return false;
    }
}
