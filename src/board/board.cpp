#include <vector>
#include <iostream>
#include <random>

class Board {
    private:
        int grids;
        int rows;
        int columns;
        std::vector<std::vector<std::vector<int>>> board;

        void generateBoard() {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist9(1,9);

            int test = dist9(rng);
            std::cout << test << std::endl;
            board[0][0][0] = test;
        }

    public:
        Board(int grids_, int rows_, int columns_) : 
            grids(grids_), rows(rows_), columns(columns_),
            board(grids_, std::vector<std::vector<int>>(rows_, std::vector<int>(columns, 0)))
        {
            generateBoard();
        }

        void printBoard() {
            // Loop Through All Rows
            for (auto row = 0; row < (rows); row++) {
                // Loop Through Grid By Grid
                for (auto grid = 0; grid < grids; grid++) {
                    // Loop Through Column And Print
                    for (auto column = 0; column < columns; column++) {
                        std::cout << " " << board[grid][row][column] << " ";
                    }
                    std::cout << "|";
                }
                std::cout << "\n";
            }
        }
};


int main() {

    Board test_board(3,3,3);

    test_board.printBoard();

    return 1;
}

