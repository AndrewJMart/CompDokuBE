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
        std::vector<std::vector<int>> playable_board;

        // Private Methods
        
        // Generation Funcs
        bool fillBoard(int row, int col, std::mt19937& rng);
        void generateBoard();
	    void uniqueBoard(std::vector<std::vector<int>>& board, int& count);
        void createPlayableBoard(std::vector<std::vector<int>> board);

        // Logical Solver Funcs
        bool logicalSolver(std::vector<std::vector<int>> board);
        bool nakedSingles(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set);
        bool hiddenSingles(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set);

        // Util Funcs
        bool isValidPosition(std::vector<std::vector<int>>& board, int row, int col);
        bool isValid(std::vector<std::vector<int>>& board);
	    void findNextEmpty(std::vector<std::vector<int>>& board, int& next_row, int& next_col);
        void createCandidateSet(std::vector<std::vector<int>>& board, std::vector<std::vector<int>>& candidate_set);

        
    public:
        // Constructor
        Board();

        // Public Methods
        void printBoard(std::vector<std::vector<int>> print_board);
};
