/**
 * An artificial intelligence that is able to play Reversi.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 07.05.2019
 **/
#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

struct Coord ai_make_move(struct Board *board, int player);

#endif // BOARD_H_INCLUDED

