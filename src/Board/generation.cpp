#include "board.h"
#include<unistd.h>

Board::Board(): 
    rows(9), cols(9), 
    board(rows, std::vector<int>(cols)), 
    playable_board(rows, std::vector<int>(cols))
    {
        generateBoard();
        printBoard(board);
        createPlayableBoard(board);
        printBoard(playable_board);
    }

void Board::generateBoard() {
    std::random_device dev;
    std::mt19937 rng(dev());

    fillBoard(0, 0, rng);
}

bool Board::fillBoard(int row, int col, std::mt19937& rng) {
    // Base Case: If Board Full & isValid Board Solved
    if (row == rows)
        return true;

    // At This Point, Board Is Valid
    // Try Different Values And Test Validitity
    std::vector<int> sudoku_values = {1,2,3,4,5,6,7,8,9};
    shuffle(sudoku_values.begin(), sudoku_values.end(), rng);

    // Loop Through Shuffled Possible Values
    for (int value : sudoku_values) {
        board[row][col] = value;

        int next_row = row;
        int next_col = col;

        // If Assigned Value Is Valid, Call Fill Board With Next Cell
        if (isValidPosition(board, row, col)) {
            // If At End Of Row, Increment Row & Reset Column
            if ( (col + 1) == cols ) {
                next_row++;
                next_col = 0;
            }
            else {
                next_col++;
            }

            if (fillBoard(next_row, next_col, rng))
                return true;
        }
    }
    // If Valid Value Not Possible. Backtrack
    board[row][col] = 0;
    return false;
}

void Board::createPlayableBoard(std::vector<std::vector<int>> board) {
    // Given A Fully Solved Board, Iteratively Remove Pieces
    std::random_device dev;
    std::mt19937 rng(dev());

    std::vector<std::pair<int, int>> cells;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            cells.emplace_back(row, col);
        }
    }

    std::shuffle(cells.begin(), cells.end(), rng);

    int max_missing = 10;
    int missing_count = 0;

    // Iterate Through Shuffled Cells
    for (auto cell : cells) {
        int row = cell.first;
        int col = cell.second;
        //unsigned int microsecond = 1000000;
                
        int original_value = board[row][col];

        if (original_value == 0)
            continue;

    
        //std::cout << "Original Value: " << original_value << std::endl;

        board[row][col] = 0;

        // Check If Board Yields uniqueBoard
        auto unique_board = board;
            
        //std::cout << "Board Passed Into Unique Solver" << std::endl;
        //printBoard(unique_board);
           
        int num_solutions = 0;
        uniqueBoard(unique_board, num_solutions);

        //usleep(10 * microsecond);

        //std::cout << "Number Of Solutions: " << num_solutions << std::endl;

        // If Board Has Multiple Solutions, Pass Onto Next Cell
        if (num_solutions != 1) {
            board[row][col] = original_value;
            continue;
        }

        //std::cout << "Board Passed Into Logical Solver" << std::endl;
        //printBoard(board);

        //usleep(10 * microsecond);

        // logicalSolver Copies Board,
        auto test_board = board;
        bool solvable = logicalSolver(test_board);

        if (!solvable)
            board[row][col] = original_value;

        // At This Point Solvable And Unique Add To Count
        missing_count++;
        if (missing_count == max_missing)
            break;
    }

    playable_board = board;
    return;
}

void Board::uniqueBoard(std::vector<std::vector<int>>& board, int& count) {
    // Passed In: Current State Of Board, counter for solutions
    // Pass In By Reference So State Carries Over During Recursion

    // Base Case: If Count > 1, Board Is Not Unique, Break Recursion & Return
    if (count > 1)
        return;

    int next_row = -1;
    int next_col = -1;

    findNextEmpty(board, next_row, next_col);

    //std::cout << "Next Empty: " << next_row << " " << next_col << std::endl;

    // If No Next Cell, Board Is Solved
    if (next_row == -1) {
        //std::cout << "Board Solved" << std::endl;
        count++;
        return;
    }

    // If Empty Cell, Iterate Through Possible Values
    std::vector<int> possibleValues = {1,2,3,4,5,6,7,8,9};
    
    for (int value : possibleValues) {
        board[next_row][next_col] = value;
        
        // If Valid Placement, Continue Along Board Filled At Spot
        bool valid_position = isValidPosition(board, next_row, next_col);
        //std::cout << "Value: " << value << " Is Valid: " << valid_position << std::endl;

        //std::cout << "Board Passed In To Valid Position" << std::endl;
        //printBoard(board);

        //int microsecond = 1000000;
        //usleep(microsecond);

        if (valid_position) {
            //std::cout << "Valid Position: " << next_row << " " << next_col << std::endl;
            //std::cout << "Valid Number: " << board[next_col][next_col] << std::endl;
            uniqueBoard(board, count);

            //int microsecond = 1000000;
            //usleep(3 * microsecond);
        }

        // If Multiple Solutions Backtrack And Prune Early
        if (count > 1) {
            board[next_row][next_col] = 0;
            return;
        }
    }

    // Backtrack If Necessary
    board[next_row][next_col] = 0;
    return;
}

bool Board::logicalSolver(std::vector<std::vector<int>>& board){
    // Given A Board, Iteratively Apply Human Solver Techniques Until Board
    // Is Solved Or Not

    // Create Candidate Set For Original Board
    std::vector<std::vector<int>> candidate_set(rows, std::vector<int>(cols, 0x1FF));

    bool progress = true;

    while(progress) {
        createCandidateSet(board, candidate_set);
        progress = nakedSingles(board, candidate_set);
    }

    // Return Case: If At End Of Progress, Board Is Solved, Return True
    if (isValid(board)) {
        return true;
    }
    else {
        return false;
    }
}
