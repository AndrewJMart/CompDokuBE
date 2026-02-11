// src/BackendUtil/BackendUtil.h

#pragma once

#include <crow.h>
#include <queue>

#include "../Match/Match.h"

void removeConnection(std::queue<crow::websocket::connection*>& playerQueue, const crow::websocket::connection* playerConnection);

void cleanUpGame(crow::websocket::connection* playerConnection,
    std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
    std::unordered_map<std::string, Match*>& uniqueIDToMatch
);

void handleMove(crow::websocket::connection* player,
                const crow::json::rvalue& messageJSON,
                std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
                std::unordered_map<std::string, Match*>& uniqueIDToMatch);

void handleSolved(crow::websocket::connection* player,
                  std::unordered_map<crow::websocket::connection*, std::string>& playerToMatch,
                  std::unordered_map<std::string, Match*>& uniqueIDToMatch);