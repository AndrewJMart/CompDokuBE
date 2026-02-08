#include <iostream>
#include <string>
#include <fstream>
#include <crow.h>
#include <queue>
#include <unordered_map>
#include <mutex>

// Import Sudoku Board Class
#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"
#include "Match/Match.h"

int main(){
    crow::SimpleApp app;
    
    // Concurrency Lock
    std::mutex mtx;

    // Hashmap: Connection -> Unique Match ID
    std::unordered_map<crow::websocket::connection*, std::string> playerToMatch;

    // Hashmap: Unique ID -> Match
    std::unordered_map<std::string, Match*> uniqueIDToMatch;

    // Queue: Store Waiting Users
    std::queue<crow::websocket::connection*> playerQueue;


    int matchID = 0;

    CROW_WEBSOCKET_ROUTE(app, "/ws/compete")
      .onopen([&](crow::websocket::connection& conn) {
          CROW_LOG_INFO << "new websocket connection from " << conn.get_remote_ip();
          std::lock_guard<std::mutex> _(mtx);

          if (playerQueue.empty()) {
            playerQueue.push(&conn);
          } else {
            // Grab First Player Off Of Queue
            crow::websocket::connection* otherPlayer = playerQueue.front();
            playerQueue.pop();

            // Create Match Between Two Players
            std::string matchIDStr = std::to_string(matchID);

            playerToMatch[&conn] = matchIDStr;
            playerToMatch[otherPlayer] = matchIDStr;

            // Create Board
            Generator gen(9,9);
            
            Board starterBoard = gen.getPlayableBoard();

            Match* playerMatch = new Match(&conn, otherPlayer, starterBoard, starterBoard);

            uniqueIDToMatch[matchIDStr] = playerMatch;

            // Send Boards To Players
            crow::json::wvalue p1ReturnJSON;
            p1ReturnJSON["type"] = "MATCH_START"; 
            p1ReturnJSON["board"] = starterBoard.getBoard();


            crow::json::wvalue p2ReturnJSON;
            p2ReturnJSON["type"] = "MATCH_START"; 
            p2ReturnJSON["board"] = starterBoard.getBoard();

            conn.send_text(p1ReturnJSON.dump());
            otherPlayer->send_text(p2ReturnJSON.dump());
          }
      })
      .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
          CROW_LOG_INFO << "websocket connection closed: " << reason;
          std::lock_guard<std::mutex> _(mtx);
      })
      .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool is_binary) {
          CROW_LOG_INFO << "Websocket Info Sent: " << data;

          // Read Data Into JSON
          auto messageJSON = crow::json::load(data);

          std::string matchIDStr = playerToMatch[&conn];
          Match* playerMatch = uniqueIDToMatch[matchIDStr];


          if (messageJSON["type"] == "MOVE") {
            crow::json::wvalue moveJSON;
            moveJSON["type"] = "MOVE_RESULT";
            moveJSON["row"] = messageJSON["row"];
            moveJSON["col"] = messageJSON["col"];

            if (&conn == playerMatch->p1) {
                playerMatch->p1Board.setCell(
                    messageJSON["row"].i(), 
                    messageJSON["col"].i(),
                    messageJSON["value"].i()
                );

                moveJSON["grid"] = playerMatch->p1Board.getBoard();

            } else {
                playerMatch->p2Board.setCell(
                    messageJSON["row"].i(), 
                    messageJSON["col"].i(),
                    messageJSON["value"].i()
                );
                moveJSON["grid"] = playerMatch->p2Board.getBoard();
            }
            conn.send_text(moveJSON.dump());
          }

          if (messageJSON["type"] == "SOLVED") {
            crow::json::wvalue solvedJSON;
            solvedJSON["type"] = "GAME_OVER";

            if (&conn == playerMatch->p1) {                
                if (!Validator::isValid(playerMatch->p1Board)) {
                    solvedJSON["type"] = "SOVLED_INVALID";
                    playerMatch->p1->send_text(solvedJSON.dump());
                    return;
                }

                // If Valid, Send Winner To P1, Loser To P2
                solvedJSON["winner"] = "you";

                playerMatch->p1->send_text(solvedJSON.dump());

                solvedJSON["winner"] = "no";

                playerMatch->p2->send_text(solvedJSON.dump());

            } else {
                if (!Validator::isValid(playerMatch->p2Board)) {
                    solvedJSON["type"] = "SOVLED_INVALID";
                    playerMatch->p2->send_text(solvedJSON.dump());
                    return;
                }

                // If Valid, Send Winner To P2, Loser To P1
                solvedJSON["winner"] = "you";

                playerMatch->p2->send_text(solvedJSON.dump());

                solvedJSON["winner"] = "no";

                playerMatch->p1->send_text(solvedJSON.dump());
            }
          }
      });

    // Default Endpoint
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(app, "/api/generateBoard")([](){

        Generator gen(9,9);

        Board playableBoard = gen.getPlayableBoard();

        crow::json::wvalue returnBoard;
        returnBoard["Board"] = playableBoard.getBoard();

        Validator::printBoard(playableBoard);

        return returnBoard;
    });
    
    // Single Thread App
    app.port(18080).bindaddr("127.0.0.1").multithreaded().run();
}
