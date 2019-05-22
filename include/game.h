/**
 * Represents a game of Reversi
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 03.04.2019
 **/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

typedef enum {Human, Cpu} Type;

typedef struct {
    Type type;
} Player;

typedef struct {
    struct Board board;
    int player;
    int last_turn_passed;
    int is_game_over;
    time_t timer;
    int seconds;
    struct Coord cursor;
    Player players[2];
} Game;

void start();

#endif // GAME_H_INCLUDED
