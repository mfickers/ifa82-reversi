/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 25.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

/**
 * Resets a given board for a new game
 * @param board: Pointer to a Board
 */
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

/**
 * Counts every marker of a given player
 * @param board: Pointer to a Board
 * @param player: Number of the Player (1 or 2)
 * @return number of points
 */
int count_points(struct Board *board, int player)
{
    int points = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // increase counter, if field-value matches player-number
            if (board->fields[x][y] == player) {
                points++;
            }
        }
    }

    return points;
}

/**
 * Counts every marker on a given board
 * @param board: Pointer to a Board
 * @return number of markers
 */
int count_markers(struct Board *board)
{
    int markers = 0;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // increase counter, if field-value is not 0
            if (board->fields[x][y] != 0) {
                markers++;
            }
        }
    }

    return markers;
}

/**
 * Checks if a given field is empty
 * @param board: Pointer to a Board
 * @param coord: Coordinates of the field on the board (e.g. 4|5)
 * @return 1 if field is empty, 0 if not
 */
int is_field_empty(struct Board *board, struct Coord coord)
{
    if (board->fields[coord.x][coord.y] == 0) {
        return 1;
    }

    return 0;
}


/**
 * Checks the validty of a given field for a given direction
 * @param board: Pointer to a Board
 * @param coord: Coordinates of the field on the board (e.g. 4|5)
 * @param player: Number of the Player (1 or 2)
 * @param direction: Coordinates representing the direction to be checked (e.g.-1|-1)
 * @return 1 if direction is valid, 0 if not
 */
int check_direction(struct Board *board, struct Coord coord, int player, struct Coord direction)
{
    // get enemy based on given player
    int enemy = 0;
    if (player == 1) {
        enemy = 2;
    } else {
        enemy = 1;
    }

    int foundEnemy = 0;
    while (1) {
        // go further in given direction
        coord.x += direction.x;
        coord.y += direction.y;
        // check, if the end of the field is reached
        if (coord.x < 0 || coord.x > 7) {
            break;
        }
        if (coord.y < 0 || coord.y > 7) {
            break;
        }
        // if an friendly field has been found after an enemy-field, validate field
        if (board->fields[coord.x][coord.y] == player && foundEnemy) {
            return 1; // Field is valid;
        // remember if an enemy field has been found
        } else if (board->fields[coord.x][coord.y] == enemy) {
            foundEnemy = 1;
        // if the first field is empty or friendly, stop checking
        } else {
            break;
        }
    }

    return 0;
}

/**
 * Checks if a given field is valid for a given player
 * @param board: Pointer-Variable to a Board
 * @param coord: Coordinates of the field on the board (e.g. 4|5)
 * @param player: Number of the Player (1 or 2)
 * @return 1 if field is valid, 0 if not
 */
int is_field_valid(struct Board *board, struct Coord coord, int player)
{
    if (!is_field_empty(board, coord)) {
        return 0; // Field is already set
    }

    // Directions representing the fields around the given field
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

    // Check every direction
    for (int i = 0; i < 8; i++) {
        if (check_direction(board, coord, player, direction[i])) {
            return 1;
        }
    }

    return 0;
}

/**
 * Sets a marker on the Board for a given player at a given location
 * @param board: Pointer-variable to a Board
 * @param coord: Coordinates of the field to be marked (e.g. 4|5)
 * @param player: Number of the Player (1 or 2)
 */
void set_marker(struct Board *board, struct Coord coord, int player)
{
    // mark field with the number of the player
    board->fields[coord.x][coord.y] = player;
}
