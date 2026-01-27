#pragma once

#include <vector>
#include <random>
#include <algorithm>

class Board {
    private:
        // Private Members
        int cols;
        int rows;
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> solveboard;

        // Private Methods
        bool fillBoard(int row, int col, std::mt19937& rng);
        void generateBoard();

	void uniqueBoard(std::vector<std::vector<int>>& board, int& count);
	void findNextEmpty(std::vector<std::vector<int>>& board, int& next_row, int& next_col);

        bool isValidPosition(int row, int col);
        bool isValid();

    public:
        // Constructor
        Board();

        // Public Methods
        void printBoard();
};
