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

// The data of the current game
Game game;

/**
 * Render passing message and wait for input
 *
 * @param int player: The player that has to pass.
 */
void _pass(int player)
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
int _can_make_turn(int player)
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
 * Get user input for a valid move
 *
 * @param int player: The player making the move
 *
 * @return struct Coord: The move chosen
 **/
struct Coord _human_make_move(int player)
{
    // Get user input until valid move made
    UserInput user_input;
    do {
        user_input = input_move(&game.board, get_game_time(), game.player, game.cursor);
        // Remember cursor position whether move is valid or not
        game.cursor = user_input.cursor;
        // Pause the game if user requested a pause
        if (user_input.input == Paused) {
            // Remember game time because timer will reset after pause
            game.seconds = get_game_time();
            render_menu(Pause);
            // Handle pause menu
            MenuInput menu_input;
            // Stay in menu until continued or quit
            do {
                menu_input = input_menu(Pause);
                if (menu_input == Save) {
                    // Save the game
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
                    // Exit pause menu
                    render_game(&game.board, get_game_time(), game.cursor, player);
                }
            } while (menu_input != Continue);
        }
    } while (user_input.input == Paused || !is_field_valid(&game.board, game.cursor, player));

    return game.cursor;
}

/**
 * Represents a turn
 *
 * @param int player: The player playing this turn
 * @param Type type: Wether the player is human or AI.
 *
 * @return int: The player having the next turn
 */
int _turn(int player, Type type)
{
    draw_turn_message(player);
    // Update game screen
    render_game(&game.board, get_game_time(), game.cursor, player);
    // If there is no valid move, the player will have to pass
    if (_can_make_turn(player)) {
        if (type == Human) {
            // get user move
            game.cursor = _human_make_move(player);
        } else {
            // get AI move
            game.cursor = ai_make_move(&game.board, player);
        }
        // apply game logic to move
        process_move(&game.board, game.cursor, player);
        // Reset pass counter
        game.last_turn_passed = 0;
    } else if (game.last_turn_passed) {
        // Two passes in a row => GAME OVER!
        game.is_game_over = 1;
    } else {
        // Force player to pass, because no valid moves
        _pass(game.player);
        // Remember the pass for next turn
        game.last_turn_passed = 1;
    }

    return next_player(game.player);
}

/**
 * Initialize all game variables for a new game
 **/
void _init_game()
{
    // Initialize variables
    init_board(&game.board);
    time(&game.timer); // Start Timer
    game.seconds = 0;
    game.last_turn_passed = 0;
    game.is_game_over = 0;
    game.player = 1; // Player 1 goes first
    game.cursor.x = 0, game.cursor.y = 0; // upper left corner
}

/**
 * Start a new game, render the menus for choosing player types
 **/
void _new_game()
{
    reset_renderer();
    render_menu(PlayerOne);
    // Choose Type of player 1
    MenuInput type = input_menu(PlayerOne);
    if (type == HumanSelect) {
        game.players[0].type = Human;
    } else {
        game.players[0].type = Cpu;
    }
    reset_renderer();
    render_menu(PlayerTwo);
    // Choose Type of player 2
    type = input_menu(PlayerTwo);
    if (type == HumanSelect) {
        game.players[1].type = Human;
    } else {
        game.players[1].type = Cpu;
    }
    // Prepare a new game
    _init_game();
}

/**
 * Load a saved game
 **/
void _load_game()
{
    load_file(&game);
    // Restart game timer
    time(&game.timer);
}

/**
 * Start the game
 */
void start()
{
    // Prepare console output
    set_console_title();
    reset_renderer();
    render_menu(Select);
    // Choose between new game, load game and quit
    MenuInput input = input_menu(Select);
    switch (input) {
    case New:
        _new_game();
        break;
    case Load:
        _load_game(&game);
        break;
    case Exit:
        return;
    default:
        break;
    }
    // Exit title menu
    reset_renderer();

    // Turn after turn until game is over
    do {
        // Do a turn for the current player and set the next player
        game.player = _turn(game.player, game.players[game.player - 1].type);
    } while (!game.is_game_over);

    // The end.
    render_game_over(count_points(&game.board, 1), count_points(&game.board, 2));
}
