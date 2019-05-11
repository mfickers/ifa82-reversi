/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 25.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/game.h"
#include "../include/board.h"
#include "../include/io.h"
#include "../include/ai.h"
#include "../include/file.h"

struct Board board;
int last_turn_passed;
int is_game_over;
time_t timer;

/**
 * Get the other player based on the current player.
 *
 * @param player The player that finished their turn.
 */
int next_player(int player)
{
    player = player % 2 + 1;

    return player;
}

/**
 * Flips all enemy markers in a direction until own maker found.
 *
 * @param coord     The marker that has been set.
 * @param player    The player that set the marker.
 * @param direction The current direction to propagate.
 */
void propagate(struct Coord coord, int player, struct Coord direction)
{
    do {
        // go further in given direction
        coord.x += direction.x;
        coord.y += direction.y;

        // Flip the markers for player until own marker found.
        if (board.fields[coord.x][coord.y] == player) {
            return;
        } else {
            set_marker(&board, coord, player);
        }
    } while (1);
}

/**
 * Set and flip all markers for this turn according to the rules.
 *
 * @param move   The position of the marker that will be set this turn.
 * @param player The player that set the marker.
 */
void process_move(struct Coord move, int player)
{
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

    // Set the new stone;
    set_marker(&board, move, player);

    // Check every direction
    for (int i = 0; i < 8; i++) {
        if (check_direction(&board, move, player, direction[i])) {
            // Flip enemy markers in this direction.
            propagate(move, player, direction[i]);
        }
    }
}

/**
 * Render passing message and wait for input
 *
 * @param player The player that has to pass.
 */
void pass(int player)
{
    render_pass(player);
}

/**
 * Represents a turn
 *
 * @param player The player that has this turn
 * @param type   Wether the player is human or AI.
 */
int turn(int player, Type type)
{
    render_board(&board);

    // Check if player can make a valid turn
    int valid_field = 0;
    struct Coord coord;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            coord.x = x;
            coord.y = y;
            if (is_field_valid(&board, coord, player)) {
                valid_field = 1;
                // A single valid move is enough
                goto after_validation;
            }
        }
    }
    after_validation: ;
    if (valid_field) {
        // Player has to move if he can
        struct Coord move;
        // Get a move from input or AI until valid move given
        do {
            if (type == Human) {
                move = input_move(player);
            } else {
                move = ai_make_move(&board, player);
            }
        } while (!is_field_valid(&board, move, player));
        process_move(move, player);
        // Reset pass counter
        last_turn_passed = 0;
    } else if (last_turn_passed) {
        // Two passes in a row => GAME OVER!
        is_game_over = 1;
    } else {
        // Notify of forced pass
        pass(player);
        // Remember the pass for next turn
        last_turn_passed = 1;
    }

    return next_player(player);
}

/**
 * Start the game
 */
void start()
{
    time(&timer); // Start Timer
    set_console_title();
    printf("-------- R E V E R S I --------\n\n");

    // Initialize variables
    init_board(&board);
    int player = 1;
    Player players[2];
    players[0].type = Human;
    players[1].type = Cpu;
    last_turn_passed = 0;
    is_game_over = 0;

    // Turn after turn until game is over
    do {
        time_t now;
        time(&now);
        render_time(difftime(now, timer));
        render_score(count_points(&board, 1), count_points(&board, 2));

        // Do a turn for the current player and set the next player
        player = turn(player, players[player - 1].type);
    } while (!is_game_over);

    // The end.
    render_game_over(count_points(&board, 1), count_points(&board, 2));
}
