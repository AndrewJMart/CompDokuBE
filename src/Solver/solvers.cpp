// src/Solver/solvers.cpp

#include "Solver.h"
#include "../Board/Board.h"
#include "../CandidateTracker/CandidateTracker.h"

bool Solver::nakedSingles(Board& board, CandidateTracker candidates) {
    // Naked Singles:
    // Apply When Cell Only Has One Candidate Left! Simply Place Single Candidate Into Board

    int rows = board.getRows();
    int cols = board.getCols();

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int boardValue = board.getCell(row, col);

            if (boardValue != 0)
                continue;

            // Check If Unsolved Cell Has Only One Candidate
            int candidateMask = candidates.getCellCandidates(row, col);
            
            if ( candidateMask != 0 &&
                (candidateMask & (candidateMask - 1)) == 0) {

                int candidate_value = __builtin_ctz(candidateMask) + 1;

                board.setCell(row, col, candidate_value);

                return true;
            }
        }
    }

    return false;
}
