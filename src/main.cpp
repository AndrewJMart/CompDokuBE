#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <crow.h>

// Import Sudoku Board Class
#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"

int main(){

    std::cout << "Initializing Backend";

    std::cout << "Reading Backend Config";

    crow::SimpleApp app;

    // Default Endpoint
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(app, "/generateBoard")([](){

        Generator gen(9,9);

        Board playableBoard = gen.getPlayableBoard();

        crow::json::wvalue returnBoard;
        returnBoard["Board"] = playableBoard.getBoard();

        Validator::printBoard(playableBoard);

        return returnBoard;
    });

    // Single Thread App
    app.port(18080).multithreaded().run();
}
