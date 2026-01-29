#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

class Board {
    private:
        // Private Members
        int cols;
        int rows;
        std::vector<std::vector<int>> board;
        std::vector<std::vector<int>> solveboard;

        // Private Methods
        
        // Generation Funcs
        bool fillBoard(int row, int col, std::mt19937& rng);
        void generateBoard();
	    void uniqueBoard(std::vector<std::vector<int>>& board, int& count);
        bool logicalSolver(std::vector<std::vector<int>> board);

        // Util Funcs
        bool isValidPosition(std::vector<std::vector<int>>& board, int row, int col);
        bool isValid();
	    void findNextEmpty(std::vector<std::vector<int>>& board, int& next_row, int& next_col);
        void createCandidateSet(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set);

    public:
        // Constructor
        Board();

        // Public Methods
        void printBoard();
};
