// src/Generator/Generator.h

#pragma once

#include "../Board/Board.h"
#include "../CandidateTracker/CandidateTracker.h"
#include <random>

class Generator {
    private:
        // Private Members
        Board solvedBoard;
        Board playableBoard;
        std::mt19937 randomNumberGenerator;

        // Generation Funcs
        bool fillBoard(int row, int col);
        void generateBoard();
        void createPlayableBoard();

        // Util Funcs
        std::mt19937 createRandomNumberGenerator();
	    void findNextEmpty(const Board& board, int& next_row, int& next_col);
        void uniqueBoard(Board& playableBoard, int& count);
        
    public:
        // Constructor
        Generator(int rows, int cols);

        // Public Methods
        Board getSolvedBoard();
        Board getPlayableBoard();
};
