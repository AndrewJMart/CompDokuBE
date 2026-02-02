// src/CandidateTracker/CandidateTracker.h

#pragma once

#include <vector>

#include "../Board/Board.h"

class CandidateTracker {
    private:
        // Private Members
        const Board& candidateBoard; // Store Reference To Board For Updating Purposes
        std::vector<std::vector<int>> candidateMask;
        
        // Private Methods
        void updateCandidateMask();
        void setCandidate(int row, int col, int value);
        
    public:
        // Constructor
        CandidateTracker(const Board& board);

        // Public Methods
        void refresh();
        int getCellCandidates(int row, int col) const;
};