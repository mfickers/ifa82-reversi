/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 10.04.2019
 **/
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


struct Coord {
    int x;
    int y;
};

struct Board {
    char fields[8][8];
};

int next_player(int player);
void propagate(struct Board *board, struct Coord coord, int player, struct Coord direction);
void process_move(struct Board *board, struct Coord move, int player);
void init_board(struct Board *board);
int count_points(struct Board *board, int player);
int count_markers(struct Board *board);
int is_field_empty(struct Board *board, struct Coord coord);
int is_field_valid(struct Board *board, struct Coord coord, int player);
void set_marker(struct Board *board, struct Coord coord, int player);
int check_direction(struct Board *board, struct Coord coord, int player, struct Coord direction);

#endif // BOARD_H_INCLUDED

