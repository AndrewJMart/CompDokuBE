// src/Match/Match.h

#pragma once

#include <vector>
#include <crow.h>

#include "../Board/Board.h"

struct Match {
    public:
        // Store Pointers To Player Connections By Value
        crow::websocket::connection* p1;
        crow::websocket::connection* p2;

        // Store Board By Value
        Board p1Board;
        Board p2Board;
        
        Match(
            crow::websocket::connection* _p1, crow::websocket::connection* _p2, Board& b1, Board& b2 
        );
};