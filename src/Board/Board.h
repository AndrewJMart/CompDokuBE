// src/Board/Board.h

#pragma once

#include <vector>

class Board {
    private:
        // Private Members
        int cols;
        int rows;
        std::vector<std::vector<int>> board;
        
    public:
        // Constructor
        Board(int row, int col);

        // Public Methods
        int getCols() const;
        int getRows() const;
        int getCell(int row, int col) const;
        void setCell(int row, int col, int value);
};