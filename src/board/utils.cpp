#include "board.h"

bool Board::isValidPosition(std::vector<std::vector<int>>& board, int row, int col) {
    int posValue = board[row][col];

    // Check If Valid Along Rows
    for (int col_check = 0; col_check < cols; col_check++){
        if (col == col_check)
            continue;
        
        if (posValue == board[row][col_check])
            return false;
    }

    // Check If Valid Along Cols
    for (int row_check = 0; row_check < rows; row_check++){
            if (row == row_check)
                continue;

            if (posValue == board[row_check][col])
                return false;
    }

    // Check If Valid Within SubMatrix
    int row_start = (row / 3) * 3;
    int col_start = (col / 3) * 3;

    for (int row_idx = row_start; row_idx < (row_start + 3); row_idx++){
        for (int col_idx = col_start; col_idx < (col_start + 3); col_idx ++){
            if (row_idx == row && col_idx == col)
                continue;

            if (posValue == board[row_idx][col_idx])
                return false;
        }
    }
    return true;
}

bool Board::isValid(std::vector<std::vector<int>>& board) {
    // Create Vectors To Store Bit Representations
    std::vector<int> rowchecker(rows);
    std::vector<int> colchecker(cols);
    std::vector<int> matrixchecker(9);

    // Loop Through All Values
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // If Empty Continue
            if (board[row][col] == 0)
                return false;
            
            // Position Value In Bitmask
            int pos = 1 << (board[row][col] - 1);

            // Check If Exists In Row
            if (rowchecker[row] & pos)
                return false;

            // Check if Exists In Column
            if (colchecker[col] & pos)
                return false;

            // Check If Value Exists In Matrix
            int row_location = row / 3;
            int col_location = col / 3;
            int matrix_value = (row_location * 3) + col_location;

            if (matrixchecker[matrix_value] & pos)
                return false;

            // Mark Value As Seen
            rowchecker[row] |= pos;
            colchecker[col] |= pos;
            matrixchecker[matrix_value] |= pos;
        }
    }
    return true;
}

void Board::findNextEmpty(std::vector<std::vector<int>>& board, int& next_row, int& next_col) {
    // Iterate Through Board & Find Indices Of Next Empty Cell
    for (int row_idx = 0; row_idx < rows; row_idx++) {
        for (int col_idx = 0; col_idx < cols; col_idx++) {
            if (board[row_idx][col_idx] == 0) {
                next_row = row_idx;
                next_col = col_idx;
                return;
            }
        }
    }
}

void Board::createCandidateSet(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set) {
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
    }

    // Iterate Through List & Update Candidate Set
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            // If Cell Is Given, Set Candidate Set To Just That Number
            if (board[row][col] != 0) {
                int pos = 1 << (board[row][col] - 1);
                // Flag Value As Only Valid Candidate
                candidate_set[row][col] &= 0;
                candidate_set[row][col] |= pos;
            }
            // If Cell Is Not Given, Take Complement Of Each Mask
            int row_location = row / 3;
            int col_location = col / 3;
            int matrix_value = (row_location * 3) + col_location;
            int used = col_mask[col] | row_mask[row] | matrix_mask[matrix_value];
            
            candidate_set[row][col] &= (~used) & 0x1FF;
        }
    }
}

void Board::printBoard() {
    // Loop Through Rows
    for (int row = 0; row < rows; row ++) {
        // Loop Through Columns
        for (int col = 0; col < cols; col++) {
            std::cout << board[row][col] << " | ";
        }
        std::cout << std::endl;
    }
}
