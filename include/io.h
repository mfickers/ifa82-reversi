/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 28.04.2019
 **/
#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

void set_console_title();
void render_board(struct Board *board);
struct Coord input_move(int player);
void render_pass(int player);
void render_game_over(int score_1, int score_2);
void render_score(int score_1, int score_2);
void render_time(int seconds);

#endif // IO_H_INCLUDED
