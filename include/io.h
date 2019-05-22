/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 28.04.2019
 **/
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

typedef enum {Select, PlayerOne, PlayerTwo, Pause} MenuState;
typedef enum {Continue, Exit, Load, Save, New, Invalid, HumanSelect, CpuSelect} MenuInput;

void set_console_title();
struct Coord input_move(struct Board *board, int seconds, int player, struct Coord cursor);
void render_pass(int player);
void render_game_over(int score_1, int score_2);
void reset_renderer();
void render_game(struct Board *board, int seconds, struct Coord cursor);
void render_menu(MenuState state);
MenuInput input_menu();

#endif // IO_H_INCLUDED
