// src/BackendUtil/BackendUtil.h

#pragma once

#include <crow.h>
#include <queue>

void removeConnection(std::queue<crow::websocket::connection*>& playerQueue, const crow::websocket::connection* playerConnection);
