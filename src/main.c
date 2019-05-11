/**
 * Our implementation of the game Reversi, written in C.
 * Project for class IFA82.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 03.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/io.h"

void test_board()
{
    set_console_title();

    struct Board board;
    init_board(&board);
    render_board(&board);

    struct Coord coord6 = {.x = 4, .y = 5};
    set_marker(&board, coord6, 1);
    printf("\nPoints for Player One: %d\n", count_points(&board, 1));
    struct Coord coord7 = {.x = 5, .y = 5};
    set_marker(&board, coord7, 2);
    printf("\nMarkers on board: %d\n", count_markers(&board));

    struct Coord coord1 = {.x = 0, .y = 0};
    struct Coord coord2 = {.x = 3, .y = 4};
    printf("\nField (%d|%d) has empty status: %d\n", coord1.x, coord1.y, is_field_empty(&board, coord1));
    printf("\nField (%d|%d) has empty status: %d\n", coord2.x, coord2.y, is_field_empty(&board, coord2));

    render_board(&board);

    struct Coord coord3 = {.x = 5, .y = 4};
    struct Coord coord4 = {.x = 0, .y = 0};
    struct Coord coord5 = {.x = 4, .y = 5};
    printf("\nIs field (%d|%d) valid for Player Two: %d\n", coord3.x, coord3.y, is_field_valid(&board, coord3, 2));
    printf("\nIs field (%d|%d) valid for Player One: %d\n", coord4.x, coord4.y, is_field_valid(&board, coord4, 1));
    printf("\nIs field (%d|%d) valid for Player One: %d\n", coord5.x, coord5.y, is_field_valid(&board, coord5, 2));
}

/**
 * Start.
 **/
int main()
{
    start();
    return 0;
}
