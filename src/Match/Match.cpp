#include <crow.h>

#include "Match.h"
#include "../Board/Board.h"

Match::Match(crow::websocket::connection* _p1, crow::websocket::connection* _p2, Board& b1, Board& b2):
    p1(_p1), p2(_p2),
    p1Board(b1),
    p2Board(b2) {}