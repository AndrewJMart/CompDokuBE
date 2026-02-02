// src/Generator/Generator.cpp

#include "Generator.h"

Generator::Generator(int rows, int cols): 
    solvedBoard(rows, cols),
    playableBoard(rows, cols),
    randomNumberGenerator(createRandomNumberGenerator()) {
    
    // 1: Generate Random Board
    generateBoard();

    // 2. Generate Playable Board
    createPlayableBoard();

}

Board Generator::getSolvedBoard() {
    return solvedBoard;
}

Board Generator::getPlayableBoard() {
    return playableBoard;
}