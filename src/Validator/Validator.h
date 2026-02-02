// src/Validator/Validator.h

#pragma once 

#include "../Board/Board.h"

class Validator {
    public:
        Validator();

        // Public Methods
        static bool isValidPosition(const Board& board, int row, int col);
        static bool isValid(const Board& board);
        static void printBoard(const Board& board);
};
