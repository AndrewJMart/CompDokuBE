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
    return;
}
