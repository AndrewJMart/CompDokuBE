#include <iostream>
#include <string>
#include <fstream>
#include <crow.h>
#include <queue>
#include <unordered_map>
#include <mutex>

#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"
#include "Match/Match.h"
#include "BackendUtil/BackendUtil.h"

int main() {
    crow::SimpleApp app;

    std::mutex mtx;

    // Connection -> Match ID
    std::unordered_map<crow::websocket::connection*, std::string> playerToMatch;

    // Match ID -> Match*
    std::unordered_map<std::string, Match*> uniqueIDToMatch;

    // Queue of waiting connections
    std::queue<crow::websocket::connection*> playerQueue;

    int matchIDCounter = 0;

    CROW_WEBSOCKET_ROUTE(app, "/ws/compete")
    .onopen([&](crow::websocket::connection& conn) {
        std::lock_guard<std::mutex> _(mtx);

        CROW_LOG_INFO << "New websocket connection from " << conn.get_remote_ip();

        if (playerQueue.empty()) {
            playerQueue.push(&conn);
        } else {
            crow::websocket::connection* otherPlayer = playerQueue.front();
            playerQueue.pop();

            std::string matchIDStr = std::to_string(matchIDCounter++);
            playerToMatch[&conn] = matchIDStr;
            playerToMatch[otherPlayer] = matchIDStr;

            Generator gen(9, 9);
            Board starterBoard = gen.getPlayableBoard();

            Match* playerMatch = new Match(&conn, otherPlayer, starterBoard, starterBoard);
            uniqueIDToMatch[matchIDStr] = playerMatch;

            // Send boards to both players
            crow::json::wvalue p1JSON;
            p1JSON["type"] = "MATCH_START";
            p1JSON["board"] = starterBoard.getBoard();
            conn.send_text(p1JSON.dump());

            crow::json::wvalue p2JSON;
            p2JSON["type"] = "MATCH_START";
            p2JSON["board"] = starterBoard.getBoard();
            otherPlayer->send_text(p2JSON.dump());
        }
    })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
        std::lock_guard<std::mutex> _(mtx);

        CROW_LOG_INFO << "Websocket connection closed: " << reason;

        // Remove from queue
        removeConnection(playerQueue, &conn);

        // Clean Up Match
        cleanUpGame(&conn, playerToMatch, uniqueIDToMatch);
    })
    .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool) {
        std::lock_guard<std::mutex> _(mtx);

        auto messageJSON = crow::json::load(data);
        if (!messageJSON) return;

        if (messageJSON["type"] == "MOVE") {
            handleMove(&conn, messageJSON, playerToMatch, uniqueIDToMatch);
        } else if (messageJSON["type"] == "SOLVED") {
            handleSolved(&conn, playerToMatch, uniqueIDToMatch);
        }
    });

    CROW_ROUTE(app, "/api/generateBoard")([]() {
        Generator gen(9, 9);
        Board playableBoard = gen.getPlayableBoard();
        Board solvedBoard = gen.getSolvedBoard();

        crow::json::wvalue returnBoards;
        returnBoards["playableBoard"] = playableBoard.getBoard();
        returnBoards["solvedBoard"] = solvedBoard.getBoard();
        return returnBoards;
    });

    // Start server
    app.port(18080).bindaddr("127.0.0.1").multithreaded().run();
}
