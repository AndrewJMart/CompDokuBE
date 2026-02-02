#include "board.h"
#include<unistd.h>

bool Board::nakedSingles(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set) {
    // Naked Singles:
    // Apply When Cell Only Has One Candidate Left! Simply Place Single Candidate Into Board

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (board[row][col] != 0)
                continue;

            // Check If Unsolved Cell Has Only One Candidate
            if ( candidate_set[row][col] != 0 &&
                (candidate_set[row][col] & (candidate_set[row][col] - 1)) == 0) {

                //std::cout << "Row : " << row << " " << "Col : " << col << std::endl;
                int candidate_value = __builtin_ctz(candidate_set[row][col]) + 1;
                //std::cout << "Candidate Value: " << candidate_value << std::endl;
                //std::cout << "Board Before Placing Candidate" << std::endl;
                //printBoard(board);

                //unsigned int microsecond = 1000000;
                //usleep(3 * microsecond);

                board[row][col] = candidate_value;

                //std::cout << "Board After Placing Candidate" << std::endl;
                //printBoard(board);

                //usleep(5 * microsecond);

                return true;
            }
        }
    }

    return false;
}

bool Board::hiddenSingles(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set) {
    // Hidden Singles:
    // If Candidate Is Found In Only One Cell For Given, Matrix, Col, Row, Place It.

    bool progress = false;

    // Loop Through All Rows
    for (int row = 0; row < rows; row++) {
        // For Each Row, Initialize Candidate Counting & Last Seen
        std::vector<int> candidate_count(cols);
        std::vector<std::pair<int, int>> candidate_seen(10);
        
        for (int col = 0; col < cols; col++) {
            int candidate_mask = board[row][col];

            // Loop Through Candidate Mask
            for (int digit = 1; digit < 10; digit++) {
                int digit_pos = 1 << (digit - 1);
                
                // Check If Digit In Candidate Set
                if (candidate_mask & digit_pos) {
                    candidate_count[digit]++;
                    candidate_seen[digit] = std::make_pair(row, col);
                }
            }
        }

        // Check Candidate Count To See If Hidden Single
        for (int digit = 1; digit < 10; digit++) {
            if (candidate_count[digit] == 1) {
                int row = candidate_seen[digit].first;
                int col = candidate_seen[digit].second;

                board[row][col] = digit;
                progress = true;
                return progress;
            }
        }
    }
    
    // Loop Through All Cols
    for (int col = 0; col < cols; col++) {
        // For Each Row, Initialize Candidate Counting & Last Seen
        std::vector<int> candidate_count(cols);
        std::vector<std::pair<int, int>> candidate_seen(10);
        
        for (int row = 0; row < rows; row++) {
            int candidate_mask = board[row][col];

            // Loop Through Candidate Mask
            for (int digit = 1; digit < 10; digit++) {
                int digit_pos = 1 << (digit - 1);
                
                // Check If Digit In Candidate Set
                if (candidate_mask & digit_pos) {
                    candidate_count[digit]++;
                    candidate_seen[digit] = std::make_pair(row, col);
                }
            }
        }

        // Check Candidate Count To See If Hidden Single
        for (int digit = 1; digit < 10; digit++) {
            if (candidate_count[digit] == 1) {
                int row = candidate_seen[digit].first;
                int col = candidate_seen[digit].second;

                board[row][col] = digit;
                progress = true;
                return progress;
            }
        }
    }

    return progress;

}
