// src/Generator/generate.cpp

#include <random>
#include <algorithm>

#include "Generator.h"
#include "../Validator/Validator.h"

void Generator::generateBoard() {
    fillBoard(0, 0);
}

bool Generator::fillBoard(int row, int col) {
    int rows = solvedBoard.getRows();
    int cols = solvedBoard.getCols();

    // Base Case: If Board Full & isValid Board Solved
    if (row == rows)
        return true;

    // At This Point, Board Is Valid
    // Try Different Values And Test Validitity
    std::vector<int> sudoku_values = {1,2,3,4,5,6,7,8,9};
    shuffle(sudoku_values.begin(), sudoku_values.end(), randomNumberGenerator);

    // Loop Through Shuffled Possible Values
    for (int value : sudoku_values) {
        solvedBoard.setCell(row, col, value);

        int next_row = row;
        int next_col = col;

        // If Assigned Value Is Valid, Call Fill Board With Next Cell
        if (Validator::isValidPosition(solvedBoard, row, col)) {
            // If At End Of Row, Increment Row & Reset Column
            if ( (col + 1) == cols ) {
                next_row++;
                next_col = 0;
            }
            else {
                next_col++;
            }

            if (fillBoard(next_row, next_col))
                return true;
        }
    }
    
    // If Valid Value Not Possible. Backtrack
    solvedBoard.setCell(row, col, 0);
    return false;
}