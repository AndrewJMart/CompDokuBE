#include "board.h"


bool Board::logicalSolver(std::vector<std::vector<int>> board){
    // Given A Board, Iteratively Apply Human Solver Techniques Until Board
    // Is Solved Or Not

    // Create Candidate Set For Original Board
    std::vector<std::vector<int>> candidate_set(rows, std::vector<int>(cols, 0));
    createCandidateSet(board, candidate_set);

    // Return Case: If At End Of Progress, Board Is Solved, Return True
    if (isValid(board)) {
        return true;
    }
    else {
        return false;
    }
}

void createCandidateSet(board, candidate_set) {
    // Given A Board, Create a Candidate Set

    // Create Masks For Rows, Cols, Matrices (9x9 Board Assumption)
    std::vector<int> col_mask(cols);
    std::vector<int> row_mask(rows);
    std::vector<int> matrix_mask(rows);

    // Update masks
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] == 0) {
                continue;
            }

            // Represent Number In Bit Format
            int pos = 1 << (board[row][col] - 1);

            // Bitwise Or To Set Bit
            col_mask[col] |= pos;
            row_mask[row] |= pos;
            
            // Calculate Matrix Position
            int row_location = row / 3;
            int col_location = col / 3;
            int matrix_value = (row_location * 3) + col_location;

            matrix_mask[matrix_value] |= pos;
        }

    // Iterate Through List & Update Candidate Set


    }

    // Iterate Through Boa


    return;
}
