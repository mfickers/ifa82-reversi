/**
 * Represents a game of Reversi
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 03.04.2019
 **/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

/**
 * Players can be either Human or computer-controlled
 **/
typedef enum {Human, Cpu} Type;

/**
 * For saving player-related data
 **/
typedef struct {
    Type type;
} Player;

/**
 * All necessary info to save and load a game
 **/
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

int get_game_time();
void main_menu();

#endif // GAME_H_INCLUDED
