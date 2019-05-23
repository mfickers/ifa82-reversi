/**
 * An artificial intelligence that is able to play Reversi.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 07.05.2019
 **/

#include <stdlib.h>
#include "../include/board.h"
#include "../include/ai.h"

// Multipliers for giving each strategy different weights
const double TABLE_MULTIPLIER = 1.0;
const double MOBILITY_MULTIPLIER = 1.0;

// Fixed value weigh table for upper left quarter
const int WEIGHT_TABLE[4][4] = {
    {90, 5, 50, 40},
    {5, 1, 20, 20},
    {50, 20, 30, 20},
    {40, 20, 20, 0},
};

/**
 * Mirrors a coordinate into the upper left quarter of the board
 *
 * @param struct Coord coord: Coordinate to mirror
 *
 * @return struct Coord: The mirrored coordinate
 */
struct Coord _mirror_coord(struct Coord coord)
{
    /*
     * Upper left corner's coordinates range from 0-3 both for x and y.
     * Horizontal mirroring along a vertical line between 3 and 4.
     * Vertical mirroring along a horizontal line between 3 and 4.
     */
    if (coord.x > 3) {
        coord.x = 7 - coord.x;
    }
    if (coord.y > 3) {
        coord.y = 7 - coord.y;
    }

    return coord;
}

/**
 * Weighs a field based on a "Disk-square table". Every field has it's
 * fixed value independent of player and status of the board.
 *
 * @param struct Coord field: Field to weigh.
 *
 * @return int: The calculated weight
 **/
int _weigh_field_table(struct Coord field)
{
    field = _mirror_coord(field);

    return WEIGHT_TABLE[field.x][field.y];
}

/**
 * Copies a board
 *
 * @param struct Board *origin: The original board
 * @param struct Board *board: The copy of the board
 **/
void _copy_board(struct Board *origin, struct Board *board)
{
    // Iterate over every field for both boards
    for (int x = 0; x < 7; x++) {
        for (int y = 0; y < 7; y++) {
            // Copy the field's value
            board->fields[x][y] = origin->fields[x][y];
        }
    }
}

/**
 * Weighs a move based on the difference in mobility for player and enemy.
 * Mobility is the number of possible moves.
 *
 * @param struct Board *origin: The state of the board before the move
 * @param struct Coord move: The move to evaluate
 * @param int player: The player making that move
 *
 * @return int: The calculated weight
 */
int _weigh_mobility(struct Board *origin, struct Coord move, int player)
{
    // Copy the board so we can alter the game state
    struct Board board;
    _copy_board(origin, &board);
    // We need to calculate possible moves for the enemy
    int enemy = next_player(player);

    int player_mobility = 0;
    int enemy_mobility = 0;
    int weight = 0;

    // Evaluate possible moves for player and enemy.
    struct Coord field;
    // Iterate over every field
    for (int x = 0; x < 7; x++) {
        field.x = x;
        for (int y = 0; y < 7; y++) {
            field.y = y;
            // For every valid field, a player's mobility increases by one
            if (is_field_valid(&board, field, player)) {
                player_mobility++;
            }
            if (is_field_valid(&board, field, enemy)) {
                enemy_mobility++;
            }
        }
    }

    // Maximize own mobility, minimize enemy mobility;
    weight = player_mobility - enemy_mobility;
    // Adjust weight by multiplier
    weight *= 10;
    // Don't remove extra weight for negative mobility difference
    if (weight < 0) {
        weight = 0;
    }

    // Get the enemy to pass to gain extra moves
    if (enemy_mobility == 0) {
        weight += 100;
    }

    return weight;
}

/**
 * Weighs a given move. Combines different strategies into a single weight value;
 *
 * @param struct Board *board: The board
 * @param struct Coord move: The move to evaluate
 * @param int player: The player making that move
 *
 * @return int: The calculated weight
 **/
int _weigh_move(struct Board *board, struct Coord move, int player)
{
    int weight = 0;

    // Fixed value weighing;
    weight += _weigh_field_table(move) * TABLE_MULTIPLIER;

    // Mobilty evaluation
    weight += _weigh_mobility(board, move, player) * MOBILITY_MULTIPLIER;

    // Just a bit of luck.
    weight += rand() % 10;

    return weight;
}

/**
 * Iterates over the board, evaluating all valid moves and
 * choosing the best based on its weight.
 *
 * @param struct Board *board: The board
 * @param int player: The player represented by this AI this turn
 *
 * @return struct Coord: The best possible move based on the AI
 **/
struct Coord ai_make_move(struct Board *board, int player)
{
    struct Coord move; // Current move
    struct Coord best; // Best move so far
    int weight;        // Current weight
    int max = -101;    // Best move's weight

    // Iterate board
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            move.x = x;
            move.y = y;
            // Only weigh valid moves
            if (is_field_valid(board, move, player)) {
                // Evaluate move
                weight = _weigh_move(board, move, player);
                if (weight > max) {
                    // New best move found
                    best = move;
                    max = weight;
                }
            }
        }
    };

    return best;
}
