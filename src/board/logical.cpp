#include "board.h"

bool Board::nakedSingles(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set) {
    // Naked Singles:
    // Apply When Cell Only Has One Candidate Left! Simply Place Single Candidate Into Board
    
    bool progress = false;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] != 0)
                continue;

            // Check If Unsolved Cell Has Only One Candidate
            if ((candidate_set[row][col] & (candidate_set[row][col] - 1)) == 0) {
                board[row][col] = candidate_set[row][col];
                progress = true;
            }
        }
    }

    return progress;
}
