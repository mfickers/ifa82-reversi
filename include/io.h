/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 28.04.2019
 **/
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include "board.h"

/**
 * The IO needs to now which menu to render and how to interpret the input given in a menu
 **/
typedef enum {
    Select,
    PlayerOne,
    PlayerTwo,
    Pause
} MenuState;

/**
 * The Input returned from a menu state by the IO
 **/
typedef enum {
    Continue,
    Exit,
    Load,
    Save,
    New,
    Invalid,
    HumanSelect,
    CpuSelect
} MenuInput;

/**
 * Wether the player put in a move or a pause command
 **/
typedef enum {
    Paused,
    Move
} Input;

/**
 * The Input returned during the active game by the IO
 **/
typedef struct {
    struct Coord cursor;
    Input input;
} UserInput;

void set_console_title();
UserInput input_move(struct Board *board, int seconds, int player, struct Coord cursor);
void render_pass(int player);
void render_game_over(int score_1, int score_2);
void reset_renderer();
void render_game(struct Board *board, int seconds, struct Coord cursor, int player);
void render_menu(MenuState state);
MenuInput input_menu();
void draw_message(char *message);
void render();
void reset_cursor();
void draw_turn_message(int player);

#endif // IO_H_INCLUDED
