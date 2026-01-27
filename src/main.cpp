#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include <crow.h>

// Import Sudoku Board Class
//#include "board/board.h"
//

int main(){

    std::cout << "Initializing Backend";

    std::cout << "Reading Backend Config";

    //Board test_board;
    //test_board.printBoard();

    crow::SimpleApp app;

    // Default Endpoint
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    // Single Thread App
    app.port(18080).multithreaded().run();
}
