/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 10.04.2019
 **/
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define EMPTY 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2

struct Board {
    char fields[8][8];
}

function init_board(struct Board board);

#endif // BOARD_H_INCLUDED

