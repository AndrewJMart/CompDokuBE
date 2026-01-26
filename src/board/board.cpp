#include <vector>
#include <iostream>
#include <random>

class Board {
    private:
        int rows;
        int cols;
        std::vector<std::vector<int>> board;

        void generateBoard() {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist9(1,9);

            // Fill Top Left
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    board[row][col] = dist9(rng);
                    while (!isValidPosition(row,col))
                        board[row][col] = dist9(rng);
                }
            }

            // Fill Middle


            // Fill Bottom Right

        }

        bool isValidPosition(int row, int col) {

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

        bool isValid() {
            // Create Vectors To Store Bit Representations
            std::vector<int> rowchecker(rows);
            std::vector<int> colchecker(cols);
            std::vector<int> matrixchecker(9);

            // Loop Through All Values
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    // If Empty Continue
                    if (board[row][col] == 0)
                        continue;
                    
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

    public:
        Board() : 
            rows(9), cols(9), board(rows, std::vector<int>(cols))
        {
            generateBoard();
        }

        void printBoard() {
            // Loop Through Rows
            for (int row = 0; row < rows; row ++) {
                // Loop Through Columns
                for (int col = 0; col < cols; col++) {
                    std::cout << board[row][col] << " | ";
                }
                std::cout << std::endl;
            }
            return;
        }
};


int main() {

    Board test_board;

    test_board.printBoard();
    return 1;
}

