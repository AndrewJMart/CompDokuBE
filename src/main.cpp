#include <iostream>
#include <string>
#include <fstream>
#include <crow.h>
#include <queue>
#include <unordered_map>
#include <mutex>
#include <chrono>
#include <thread>
#include <vector>

#include "Board/Board.h"
#include "Validator/Validator.h"
#include "Generator/Generator.h"
#include "Match/Match.h"
#include "BackendUtil/BackendUtil.h"

struct PlayerConnection {
    crow::websocket::connection* conn;
    std::chrono::steady_clock::time_point lastPing;
};

int main() {
    crow::SimpleApp app;

    std::mutex mtx;

    std::unordered_map<crow::websocket::connection*, PlayerConnection> activeConnections;

    std::unordered_map<crow::websocket::connection*, std::string> playerToMatch;

    std::unordered_map<std::string, Match*> uniqueIDToMatch;

    std::queue<crow::websocket::connection*> playerQueue;

    int matchIDCounter = 0;

    std::thread heartbeatThread([&]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(30));
            
            std::lock_guard<std::mutex> _(mtx);
            auto now = std::chrono::steady_clock::now();
            
            std::vector<crow::websocket::connection*> toRemove;
            
            for (auto& [conn, playerConn] : activeConnections) {
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                    now - playerConn.lastPing
                ).count();
                
                if (elapsed > 60) {
                    CROW_LOG_INFO << "Connection timeout detected for " << conn->get_remote_ip();
                    toRemove.push_back(conn);
                } else {
                    try {
                        crow::json::wvalue ping;
                        ping["type"] = "PING";
                        conn->send_text(ping.dump());
                    } catch (const std::exception& e) {
                        CROW_LOG_ERROR << "Failed to send ping: " << e.what();
                        toRemove.push_back(conn);
                    }
                }
            }
            
            for (auto* conn : toRemove) {
                CROW_LOG_INFO << "Cleaning up timed-out connection";
                cleanUpGame(conn, playerToMatch, uniqueIDToMatch);
                activeConnections.erase(conn);
                removeConnection(playerQueue, conn);
            }
        }
    });
    heartbeatThread.detach();

    CROW_WEBSOCKET_ROUTE(app, "/ws/compete")
    .onopen([&](crow::websocket::connection& conn) {
        std::lock_guard<std::mutex> _(mtx);

        CROW_LOG_INFO << "New websocket connection from " << conn.get_remote_ip();

        activeConnections[&conn] = PlayerConnection{
            &conn, 
            std::chrono::steady_clock::now()
        };

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
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t code) {
        std::lock_guard<std::mutex> _(mtx);

        CROW_LOG_INFO << "Websocket connection closed from " << conn.get_remote_ip() 
                      << " - Reason: " << reason << " - Code: " << code;

        activeConnections.erase(&conn);

        removeConnection(playerQueue, &conn);

        cleanUpGame(&conn, playerToMatch, uniqueIDToMatch);
    })
    .onmessage([&](crow::websocket::connection& conn, const std::string& data, bool) {
        std::lock_guard<std::mutex> _(mtx);

        auto messageJSON = crow::json::load(data);
        if (!messageJSON) return;

        if (activeConnections.find(&conn) != activeConnections.end()) {
            activeConnections[&conn].lastPing = std::chrono::steady_clock::now();
        }

        std::string messageType = messageJSON["type"].s();

        if (messageType == "PONG") {
            return;
        } else if (messageType == "MOVE") {
            handleMove(&conn, messageJSON, playerToMatch, uniqueIDToMatch);
        } else if (messageType == "SOLVED") {
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

    app.port(18080).bindaddr("127.0.0.1").multithreaded().run();
}