// src/Generator/Generator.h

#pragma once

#include "../Board/Board.h"
#include "../CandidateTracker/CandidateTracker.h"

class Solver {
    private:
        // Private Methods
        static bool nakedSingles(Board& board, CandidateTracker candidates);

    public:
        // Constructor
        Solver();

        // Public Methods
        static bool logicalSolver(Board& board);
};
