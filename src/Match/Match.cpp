#include <crow>

#include "Match.h"
#include "Board/Board.h"

Match::Match(crow::websocket::connection* _p1, crow::websocket::connection* _p1, const Board& b1, const Board& b2):
    p1(_p1), p1(_p1),
    p1Board(b1) 
    p2Board(b2) {}