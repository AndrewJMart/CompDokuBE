// src/test.cpp

#include <iostream>
#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"

int main() {
    std::cout << "Sudoku Generator Test\n" << std::endl;
    
    std::cout << "Generating boards...\n" << std::endl;
    
    Generator gen(9, 9);
    
    std::cout << "Solved Board:" << std::endl;
    Board solvedBoard = gen.getSolvedBoard();
    Validator::printBoard(solvedBoard);
    
    std::cout << "Playable Board:" << std::endl;
    Board playableBoard = gen.getPlayableBoard();
    Validator::printBoard(playableBoard);
    
    return 0;
}