/**
 * An artificial intelligence that is able to play Reversi.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 07.05.2019
 **/

#include <stdlib.h>
#include "../include/board.h"
#include "../include/ai.h"

/**
 * Weighs a given move.
 *
 * @param *board The board
 * @param move   The move to evaluate
 * @param player The player making that move
 **/
int weigh_move(struct Board *board, struct Coord move, int player)
{
    // Check for corners
    if (move.x == 0 || move.x == 7) {
        if (move.y == 0 || move.y == 7) {
            return 100; // Max weight for corners
        }
    }

    // Choose a random weight for other moves
    return rand() % 100 - 50;
}

/**
 * Iterates over the board, evaluating all valid moves and
 * choosing the best based on its weight.
 *
 * @param *board pointer to board
 * @param player
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
            if (is_field_valid(board, move, player)) {
                // Evaluate move
                weight = weigh_move(board, move, player);
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
