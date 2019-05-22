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

Game game;

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
 * Get the total amount of time of this match
 *
 * @return int: Game time in seconds
 **/
int get_game_time()
{
    time_t now;
    time(&now);

    // The current playtime + the sum of previous play times
    return difftime(now, game.timer) + game.seconds;
}

/**
 * Check if player can make a valid turn
 *
 * @param int player: The player to check for
 *
 * @return int:
 *     0 for no valid turns
 *     1 for at least 1 valid turn
 **/
int can_make_turn(int player)
{
    struct Coord coord;
    // Check every field
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            coord.x = x;
            coord.y = y;
            if (is_field_valid(&game.board, coord, player)) {
                // A single valid move is enough
                return 1;
            }
        }
    }

    return 0;
}

/**
 * Represents a turn
 *
 * @param int player: The player that has this turn
 * @param Type type: Wether the player is human or AI.
 *
 * @return int: The player having the next turn
 */
int turn(int player, Type type)
{
    if (can_make_turn(player)) {
        // Get a move from input or AI until valid move given
        if (type == Human) {
            UserInput user_input;
            do {
                user_input = input_move(&game.board, get_game_time(), game.player, game.cursor);
                // Remember cursor position wether move is valid or not
                game.cursor = user_input.cursor;
                if (user_input.input == Paused) {
                    // Remember game time because timer will reset after pause
                    game.seconds = get_game_time();
                    render_menu(Pause);
                    MenuInput menu_input;
                    do {
                        menu_input = input_menu(Pause);
                        if (menu_input == Save) {
                            save_file(&game);
                            char message[30];
                            sprintf(message, "The game has been saved!%c", '\0');
                            draw_message(message);
                            render();
                        } else if (menu_input == Exit) {
                            // Leave the program
                            exit(0);
                        } else if (menu_input == Continue) {
                            // Restart game timer
                            time(&game.timer);
                            reset_renderer();
                            render_game(&game.board, get_game_time(), game.cursor);
                        }
                    } while (menu_input != Continue);
                }
            } while (user_input.input == Paused || !is_field_valid(&game.board, game.cursor, game.player));
        } else {
            // AI can only make valid moves
            game.cursor = ai_make_move(&game.board, game.player);
        }
        process_move(&game.board, game.cursor, game.player);
        // Reset pass counter
        game.last_turn_passed = 0;
    } else if (game.last_turn_passed) {
        // Two passes in a row => GAME OVER!
        game.is_game_over = 1;
    } else {
        // Only way to pass is if no valid move is possible
        pass(game.player);
        // Remember the pass for next turn
        game.last_turn_passed = 1;
    }

    return next_player(game.player);
}

/**
 * Initialize all game variables for a new game
 **/
void init_game()
{
    // Initialize variables
    init_board(&game.board);
    time(&game.timer); // Start Timer
    game.seconds = 0;
    game.last_turn_passed = 0;
    game.is_game_over = 0;
    game.player = 1;
    game.cursor.x = 0, game.cursor.y = 0;
}

/**
 * Start a new game, render the menus for choosing player types
 **/
void new_game()
{
    reset_renderer();
    render_menu(PlayerOne);
    MenuInput type = input_menu(PlayerOne);
    if (type == HumanSelect) {
        game.players[0].type = Human;
    } else {
        game.players[0].type = Cpu;
    }
    reset_renderer();
    render_menu(PlayerTwo);
    type = input_menu(PlayerTwo);
    if (type == HumanSelect) {
        game.players[1].type = Human;
    } else {
        game.players[1].type = Cpu;
    }
    init_game();
}

/**
 * Load a saved game
 **/
void load_game()
{
    load_file(&game);
    // Set the clock to current time
    time(&game.timer);
}

/**
 * Start the game
 */
void start()
{
    set_console_title();

    reset_renderer();
    render_menu(Select);
    MenuInput input = input_menu(Select);
    switch (input) {
    case New:
        new_game();
        break;
    case Load:
        load_game(&game);
        break;
    case Exit:
        return;
    default:
        break;
    }

    reset_renderer();

    // Turn after turn until game is over
    do {
        render_game(&game.board, get_game_time(), game.cursor);

        // Do a turn for the current player and set the next player
        game.player = turn(game.player, game.players[game.player - 1].type);
    } while (!game.is_game_over);

    // The end.
    render_game_over(count_points(&game.board, 1), count_points(&game.board, 2));
}
