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
#include "game.h"

int save_file(Game *game);
int load_file(Game *game);

#endif // FILE_H_INCLUDED
