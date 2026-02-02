// src/Generator/playable.cpp

#include "Generator.h"
#include "../CandidateTracker/CandidateTracker.h"
#include "../Validator/Validator.h"

#include <vector>
#include <random>
#include <algorithm>

void Generator::createPlayableBoard() {
    Board board = solvedBoard;
    int rows = board.getRows();
    int cols = board.getCols();
    
    std::vector<std::pair<int, int>> cells;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cells.emplace_back(row, col);
        }
    }

    std::shuffle(cells.begin(), cells.end(), randomNumberGenerator);

    int max_missing = 10;
    int missing_count = 0;

    // Iterate Through Shuffled Cells
    for (auto cell : cells) {
        int row = cell.first;
        int col = cell.second;
                
        int original_value = board.getCell(row, col);

        if (original_value == 0)
            continue;

        // Temporarily remove value
        board.setCell(row, col, 0);

        // Check If Board Yields uniqueBoard
        Board unique_board = board;
           
        int num_solutions = 0;
        uniqueBoard(unique_board, num_solutions);

        // If Board Has Multiple Solutions, Replace Original Value
        if (num_solutions != 1) {
            board.setCell(row, col, original_value);
            continue;
        }

        // logicalSolver Copies Board
        Board test_board = board;
        bool solvable = logicalSolver(test_board);

        if (!solvable) {
            board.setCell(row, col, original_value);
            continue;
        }

        // At This Point Solvable And Unique Add To Count
        missing_count++;
        if (missing_count == max_missing)
            break;
    }

    playableBoard = board;
    return;
}

bool Generator::logicalSolver(Board& board){
    // Given A Board, Iteratively Apply Human Solver Techniques Until Board
    // Is Solved Or Not

    // Create Candidate Set For Original Board
    bool progress = true;

    while(progress) {
        CandidateTracker candidates(board);
        progress = nakedSingles(board, candidates);
    }

    // Return Case: If At End Of Progress, Board Is Solved, Return True
    if (Validator::isValid(board)) {
        return true;
    }
    else {
        return false;
    }
}