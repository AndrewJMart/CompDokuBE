//src/BackendUtil/BackendUtil.cpp

#include "BackendUtil.h"


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