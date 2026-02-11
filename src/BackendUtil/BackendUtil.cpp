//src/BackendUtil/BackendUtil.cpp

#include "BackendUtil.h"
#include "../Match/Match.h"
#include "../Validator/Validator.h"

#include <iostream>


void removeConnection(std::queue<crow::websocket::connection*>& playerQueue, const crow::websocket::connection* playerConnection) {
    std::queue<crow::websocket::connection*> newQueue;

    while(!playerQueue.empty()) {
        crow::websocket::connection* comp = playerQueue.front();
        playerQueue.pop();

        if (comp != playerConnection) {
            newQueue.push(comp);
        }
    }
    playerQueue = newQueue;
}

void cleanUpGame(
    crow::websocket::connection* playerConnection,
    std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
    std::unordered_map<std::string, Match*>& uniqueIDToMatch
) {
    auto it = playerToMatch.find(playerConnection);
    if (it != playerToMatch.end()) {
        std::string matchID = it->second;
        auto matchIt = uniqueIDToMatch.find(matchID);
        if (matchIt != uniqueIDToMatch.end()) {
            Match* playerMatch = matchIt->second;

            // Notify Other Player
            crow::websocket::connection* otherPlayer = (playerConnection == playerMatch->p1) ? playerMatch->p2 : playerMatch->p1;
            if (otherPlayer) {
                crow::json::wvalue json;
                json["type"] = "PLAYER_LEFT";
                otherPlayer->send_text(json.dump());
            }

            // Clean Up Hashmaps
            playerToMatch.erase(playerMatch->p1);
            playerToMatch.erase(playerMatch->p2);
            uniqueIDToMatch.erase(matchID);

            delete playerMatch; // Free Match Memory
        }
    }
}

void handleMove(crow::websocket::connection* player,
                const crow::json::rvalue& messageJSON,
                std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
                std::unordered_map<std::string, Match*>& uniqueIDToMatch) {
    
    auto it = playerToMatch.find(player);
    if (it == playerToMatch.end()) return;

    std::string matchID = it->second;
    auto matchIt = uniqueIDToMatch.find(matchID);
    if (matchIt == uniqueIDToMatch.end()) return;

    Match* playerMatch = matchIt->second;

    crow::json::wvalue moveJSON;
    moveJSON["type"] = "MOVE_RESULT";
    moveJSON["row"] = messageJSON["row"];
    moveJSON["col"] = messageJSON["col"];

    if (player == playerMatch->p1) {
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

    player->send_text(moveJSON.dump());
}

void handleSolved(crow::websocket::connection* player,
                  std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
                  std::unordered_map<std::string, Match*>& uniqueIDToMatch) {

    auto it = playerToMatch.find(player);
    if (it == playerToMatch.end()) return;

    std::string matchID = it->second;
    auto matchIt = uniqueIDToMatch.find(matchID);
    if (matchIt == uniqueIDToMatch.end()) return;

    Match* playerMatch = matchIt->second;

    crow::json::wvalue solvedJSON;
    solvedJSON["type"] = "GAME_OVER";

    crow::websocket::connection* winnerConn = (player == playerMatch->p1) ? playerMatch->p1 : playerMatch->p2;
    crow::websocket::connection* loserConn  = (player == playerMatch->p1) ? playerMatch->p2 : playerMatch->p1;

    auto& winnerBoard = (player == playerMatch->p1) ? playerMatch->p1Board : playerMatch->p2Board;

    if (!Validator::isValid(winnerBoard)) {
        solvedJSON["type"] = "SOLVED_INVALID";
        winnerConn->send_text(solvedJSON.dump());
        return;
    }

    solvedJSON["winner"] = "you";
    winnerConn->send_text(solvedJSON.dump());

    solvedJSON["winner"] = "no";
    loserConn->send_text(solvedJSON.dump());
}