#pragma once

#include <vector>

class CandidateTracker {
    private:
        // Private Members
        std::vector<std::vector<int>> candidateMask;
        const Board& candidateBoard; // Store Reference To Board For Updating Purposes
        
        // Private Methods
        void updateCandidateMask();
        void setCandidate(int row, int col, int value);
        
    public:
        // Constructor
        CandidateTracker(const Board& board);

        // Public Methods
        void refresh();
        int getCellCandidates(int row, int col);
};
