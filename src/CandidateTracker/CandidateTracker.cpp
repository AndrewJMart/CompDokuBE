#include "CandidateTracker.h"
#include "../Board/Board.h"

CandidateTracker::CandidateTracker(const Board& board)
    : candidateBoard(board),
      candidateMask(board.getRows(), std::vector<int>(board.getCols(), 0x1FF)) {
        updateCandidateMask();
}

void CandidateTracker::updateCandidateMask() {
    int rows = candidateBoard.getRows();
    int cols = candidateBoard.getCols();

    std::vector<int> col_mask(cols, 0);
    std::vector<int> row_mask(rows, 0);
    std::vector<int> matrix_mask(rows, 0);

    // Map Out What Is On Board
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int val = candidateBoard.getCell(r, c);
            if (val != 0) {
                int bit = 1 << (val - 1);
                row_mask[r] |= bit;
                col_mask[c] |= bit;
                matrix_mask[(r / 3) * 3 + (c / 3)] |= bit;
            }
        }
    }

    // Overwrite With New Candidates
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int val = candidateBoard.getCell(r, c);
            if (val != 0) {
                // If Cell Filled, Candidate Is Number
                setCandidate(r, c, 1 << (val - 1));
            } else {
                int used = row_mask[r] | col_mask[c] | matrix_mask[(r / 3) * 3 + (c / 3)];
                // If 0, Use Complement Of All Masks
                setCandidate(r, c, (~used) & 0x1FF); 
            }
        }
    }
}

void CandidateTracker::refresh() {
    updateCandidateMask();
}

int CandidateTracker::getCellCandidates(int row, int col) const {
    return candidateMask[row][col];
}

void CandidateTracker::setCandidate(int row, int col, int value) {
    candidateMask[row][col] = value;
}