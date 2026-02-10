//src/BackendUtil/BackendUtil.cpp

#include "BackendUtil.h"
#include "../Match/Match.h"

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
    std::unordered_map<crow::websocket::connection*, std::string> playerToMatch,
    std::unordered_map<std::string, Match*> uniqueIDToMatch
) {
    // If Player Match Already Cleaned, Return
    if (playerToMatch.find(playerConnection) == playerToMatch.end()) {
        CROW_LOG_INFO << "Check If Cleaned" << playerConnection->get_remote_ip();
        return;
    } 

    CROW_LOG_INFO << "Check MatchID" << playerConnection->get_remote_ip();
    
    // Get MatchID Affiliated With Player
    std::string playerMatchID = playerToMatch[playerConnection];

    CROW_LOG_INFO << "Check PlayerMatch" << playerConnection->get_remote_ip();

    // Get Match Object Player Is In
    Match* playerMatch = uniqueIDToMatch[playerMatchID];


    CROW_LOG_INFO << "Check Match" << playerConnection->get_remote_ip();

    crow::json::wvalue ReturnJSON;
    ReturnJSON["type"] = "PLAYER_LEFT";

    crow::websocket::connection* returnPlayer;

    if (playerConnection != playerMatch->p1) {
        returnPlayer = playerMatch->p1; 
    } else {
        returnPlayer = playerMatch->p2;
    }

    returnPlayer->send_text(ReturnJSON.dump());

    // Remove From Hashmaps
    playerToMatch.erase(playerConnection);
    playerToMatch.erase(returnPlayer);
    uniqueIDToMatch.erase(playerMatchID);

    return;
}