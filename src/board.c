/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 25.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

// Directions representing the fields around the given field
const struct Coord DIRECTION[] = {
    {.x = -1, .y = -1}, // Upper left
    {.x = -1, .y =  0}, // Up
    {.x = -1, .y =  1}, // Upper right
    {.x =  0, .y = -1}, // Left
    {.x =  0, .y =  1}, // Right
    {.x =  1, .y = -1}, // Lower left
    {.x =  1, .y =  0}, // Down
    {.x =  1, .y =  1}  // Lower right
};

/**
 * Get the other player based on the current player.
 *
 * @param int player: The player that finished their turn.
 *
 * @return int: The next player
 */
int next_player(int player)
{
    // Loops through 1 and 2
    player = player % 2 + 1;

    return player;
}

/**
 * Flips all enemy markers in a direction until own maker found.
 *
 * @param struct Board *board: The board
 * @param struct Coord coord: The marker that has been set.
 * @param int player: The player that set the marker.
 * @param struct Coord direction: The current direction to propagate.
 */
void propagate(struct Board *board, struct Coord coord, int player, struct Coord direction)
{
    do {
        // go further in given direction
        coord.x += direction.x;
        coord.y += direction.y;

        // Flip the markers for player until own marker found.
        if (board->fields[coord.x][coord.y] == player) {
            return;
        } else {
            set_marker(board, coord, player);
        }
    } while (1);
}

/**
 * Set and flip all markers for this turn according to the rules.
 *
 * @param struct Board *board: The board
 * @param struct Coord move: The position of the marker that will be set this turn.
 * @param int player: The player that set the marker.
 */
void process_move(struct Board *board, struct Coord move, int player)
{
    // Set the new stone;
    set_marker(board, move, player);

    // Check every direction
    for (int i = 0; i < 8; i++) {
        // For every direction with markers to flip
        if (check_direction(board, move, player, DIRECTION[i])) {
            // Flip enemy markers in this direction.
            propagate(board, move, player, DIRECTION[i]);
        }
    }
}

/**
 * Resets a given board for a new game
 *
 * @param struct Board *board: The board
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
 *
 * @param struct Board *board: The board
 * @param int player: Number of the Player (1 or 2)
 *
 * @return int: Number of markers for the player
 */
int count_points(struct Board *board, int player)
{
    int points = 0;

    // Iterate board
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // For every marker of player
            if (board->fields[x][y] == player) {
                // Increase player's points
                points++;
            }
        }
    }

    return points;
}

/**
 * Counts every marker on a given board
 *
 * @param struct Board *board: The board
 *
 * @return int: The total number of markers
 */
int count_markers(struct Board *board)
{
    int markers = 0;

    // Iterate board
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            // For every marker on board
            if (board->fields[x][y] != 0) {
                // Increase counter
                markers++;
            }
        }
    }

    return markers;
}

/**
 * Checks if a given field is empty
 *
 * @param struct Board *board: The board
 * @param struct Coord coord: The field to check
 *
 * @return int:
 *      1 if field is empty
 *      0 if field is not empty
 */
int is_field_empty(struct Board *board, struct Coord coord)
{
    // Is field empty?
    if (board->fields[coord.x][coord.y] == 0) {
        return 1;
    }

    return 0;
}


/**
 * Checks the validity of a given field for a given direction
 *
 * @param struct Board *board: The board
 * @param struct Coord coord: The origin field
 * @param int player: The player setting their marker on origin field
 * @param struct Coord direction: The direction to check
 *
 * @return int:
 *      1 if this direction makes this move valid
 *      0 if this direction does not make this move valid
 */
int check_direction(struct Board *board, struct Coord coord, int player, struct Coord direction)
{
    // get enemy based on given player
    int enemy = next_player(player);
    int foundEnemy = 0;

    while (1) {
        // go further in given direction
        coord.x += direction.x;
        coord.y += direction.y;
        // check, if the end of the board is reached
        if (coord.x < 0 || coord.x > 7) {
            break; // Not valid
        }
        if (coord.y < 0 || coord.y > 7) {
            break; // Not valid
        }
        // if an friendly field has been found after an enemy-field,
        if (board->fields[coord.x][coord.y] == player && foundEnemy) {
            return 1; // Field is valid;
        // if an enemy stone has been found
        } else if (board->fields[coord.x][coord.y] == enemy) {
            foundEnemy = 1; // remember
        // if there is an empty field, or a friendly marker before the first
        // enemy marker
        } else {
            break; // Not valid
        }
    }

    return 0;
}

/**
 * Checks if a given field is valid for a given player
 *
 * @param struct Board *board: The board
 * @param struct Coord coord: The field to check
 * @param int player: The player wanting to set the field
 *
 * @return int:
 *      1 if this field is valid
 *      0 if this field is not valid
 */
int is_field_valid(struct Board *board, struct Coord coord, int player)
{
    // Only empty fields can be valid
    if (!is_field_empty(board, coord)) {
        return 0; // Field is already set
    }

    // Check every direction
    for (int i = 0; i < 8; i++) {
        if (check_direction(board, coord, player, DIRECTION[i])) {
            return 1; // One valid direction suffices
        }
    }

    return 0; // Not valid
}

/**
 * Sets a marker on the Board for a given player at a given location
 *
 * @param struct Board *board: The board
 * @param struct Coord coord: The field to set
 * @param int player: The player setting the field
 */
void set_marker(struct Board *board, struct Coord coord, int player)
{
    // mark field with the number of the player
    board->fields[coord.x][coord.y] = player;
}
