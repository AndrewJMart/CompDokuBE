// src/Solver/Solver.cpp

#include "Solver.h"
#include "../Board/Board.h"
#include "../CandidateTracker/CandidateTracker.h"
#include "../Validator/Validator.h"

bool Solver::logicalSolver(Board& board){
    // Given A Board, Iteratively Apply Human Solver Techniques Until Board
    // Is Solved Or Not

    // Create Candidate Set For Original Board
    bool progress = true;

    while(progress) {
        CandidateTracker candidates(board);
        progress = Solver::nakedSingles(board, candidates);
    }

    // Return Case: If At End Of Progress, Board Is Solved, Return True
    if (Validator::isValid(board)) {
        return true;
    }
    else {
        return false;
    }
}