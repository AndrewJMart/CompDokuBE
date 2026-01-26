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

            return;

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
            std::cout << isValid();
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
        }
};


int main() {

    Board test_board;

    test_board.printBoard();

    return 1;
}

