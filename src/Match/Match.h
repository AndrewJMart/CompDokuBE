// src/Match/Match.h

#pragma once

#include <crow>
#include <vector>

#include "Board/Board.h"

struct Match {
    public:
        // Store Pointers To Player Connections By Value
        crow::websocket::connection* p1;
        crow::websocket::connection* p2;

        // Store Board By Value
        Board p1Board;
        Board p2Board;
    
        Match(
            crow::websocket::connection* _p1, crow::websocket::connection* _p1, const Board& b1, const Board& b2 
        )
}