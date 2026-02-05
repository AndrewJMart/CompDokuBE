#include <iostream>
#include <fstream>
#include <crow.h>
#include <unordered_set>
#include <mutex>

// Import Sudoku Board Class
#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"

int main(){

    std::cout << "Initializing Backend";

    std::cout << "Reading Backend Config";

    crow::SimpleApp app;
    std::mutex mtx;
    std::unordered_set<crow::websocket::connection*> users;

    CROW_WEBSOCKET_ROUTE(app, "/ws")
      .onopen([&](crow::websocket::connection& conn) {
          CROW_LOG_INFO << "new websocket connection from " << conn.get_remote_ip();
          std::lock_guard<std::mutex> _(mtx);
          users.insert(&conn);
      })
      .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
          CROW_LOG_INFO << "websocket connection closed: " << reason;
          std::lock_guard<std::mutex> _(mtx);
          users.erase(&conn);
      })
      .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary) {
          CROW_LOG_INFO << "Websocket Info Sent: " << data;

          // Read Data Into JSON
          auto messageJSON = crow::json::load(data);

          CROW_LOG_INFO << "ID" << messageJSON["ID"];

        //   std::lock_guard<std::mutex> _(mtx);
        //   for (auto u : users)
        //       if (is_binary)
        //           u->send_binary(data);
        //       else
        //           u->send_text(data);
      });

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
