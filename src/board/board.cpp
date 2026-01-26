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
        }
};


int main() {

    Board test_board;

    test_board.printBoard();

    return 1;
}

