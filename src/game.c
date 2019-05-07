/**
 * Represents a Reversi board.
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 25.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/io.h"

struct Board board;
int last_turn_passed;
int is_game_over;

/**
 * Get the other player
 */
int next_player(int player)
{
    player = player % 2 + 1;

    return player;
}

/**
 * Flips all enemy markers in a direction until own maker found.
 */
void propagate(struct Coord coord, int player, struct Coord direction)
{
    do {
        // go further in given direction
        coord.x += direction.x;
        coord.y += direction.y;

        if (board.fields[coord.x][coord.y] == player) {
            return;
        } else {
            set_marker(&board, coord, player);
        }
    } while (1);
}

/**
 * Set and flip all markers according to the rules
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
            propagate(move, player, direction[i]);
        }
    }
}

/**
 * Render passing message and wait for input
 */
void pass(int player)
{
    render_pass(player);
}

/**
 * Represents a turn
 */
int turn(int player)
{
    render_board(&board);
    int valid_field = 0;
    struct Coord coord;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            coord.x = x;
            coord.y = y;
            if (is_field_valid(&board, coord, player)) {
                valid_field = 1;
                goto after_validation;
            }
        }
    }
    after_validation: ;
    if (valid_field) {
        struct Coord move;
        do {
            move = input_move(player);
        } while (!
                 is_field_valid(&board, move, player));
        process_move(move, player);
        last_turn_passed = 0;
    } else if (last_turn_passed) {
        is_game_over = 1;
    } else {
        pass(player);
        last_turn_passed = 1;
    }

    return next_player(player);
}

/**
 * Start the game
 */
void start()
{
    set_console_title();
    printf("-------- R E V E R S I --------\n\n");
    init_board(&board);
    int player = 1;
    last_turn_passed = 0;
    is_game_over = 0;
    do {
        player = turn(player);
    } while (!is_game_over);
    render_game_over(count_points(&board, 1), count_points(&board, 2));
}
