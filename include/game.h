/**
 * Represents a game of Reversi
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 03.04.2019
 **/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

typedef enum {Human, Cpu} Type;

typedef struct {
    Type type;
} Player;

void start();

#endif // GAME_H_INCLUDED
