/**
 * File-Handling for saving the current game-state
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 10.04.2019
 **/
#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#include <time.h>
#include "../include/board.h"

struct Savestate {
    struct Board board;
    int player;
    time_t timer;
};

// TODO: Add timer
int save_file(struct Board *board, int player, int seconds);
struct Savestate get_savestate();


#endif // FILE_H_INCLUDED
