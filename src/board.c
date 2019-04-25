/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian G�rres, Fabian Heeke
 * Date: 25.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

void init_board(struct Board *board)
{
    // Erase whole board
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            board->fields[x][y] = 0;
        }
    }

    // Set starting grid
    board->fields[3][3] = 1;
    board->fields[4][4] = 1;
    board->fields[3][4] = 2;
    board->fields[4][3] = 2;
}

int count_points(struct Board *board, int player)
{
    int points = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->fields[x][y] == player) {
                points++;
            }
        }
    }

    return points;
}

int count_markers(struct Board *board)
{
    int markers = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board->fields[x][y] != 0) {
                markers++;
            }
        }
    }

    return markers;
}

int is_field_empty(struct Board *board, struct Coord coord)
{
    if (board->fields[coord.x][coord.y] == 0) {
        return 1;
    }

    return 0;
}

int check_direction(struct Board *board, struct Coord coord, int player, struct Coord direction)
{
    int enemy = 0;
    if (player == 1) {
        enemy = 2;
    } else {
        enemy = 1;
    }
    int foundEnemy = 0;
    while (1) {
        coord.x += direction.x;
        coord.y += direction.y;
        if (coord.x < 0 || coord.x > 7) {
            break;
        }
        if (coord.y < 0 || coord.y > 7) {
            break;
        }
        if (board->fields[coord.x][coord.y] == player && foundEnemy) {
            return 1; // Field is valid;
        } else if (board->fields[coord.x][coord.y] == enemy) {
            foundEnemy = 1;
        } else {
            break;
        }
    }

    return 0;
}

int is_field_valid(struct Board *board, struct Coord coord, int player)
{
    if (!is_field_empty(board, coord)) {
        return 0; // Field is already set
    }

    struct Coord direction[] = {
        {.x = -1, .y = -1}, // Upper left
        {.x = -1, .y =  0}, // Up
        {.x = -1, .y =  1}, // Upper right
        {.x =  0, .y = -1}, // Left
        {.x =  0, .y =  1}, // Right
        {.x =  1, .y = -1}, // Lower left
        {.x =  1, .y =  0}, // Down
        {.x =  1, .y =  1}  // Lower right
    };
    for (int i = 0; i < 8; i++) {
        if (check_direction(board, coord, player, direction[i])) {
            return 1;
        }
    }

    return 0;
}

void set_marker(struct Board *board, struct Coord coord, int player)
{
    board->fields[coord.x][coord.y] = player;
}
