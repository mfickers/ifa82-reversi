/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian G�rres, Fabian Heeke
 * Date: 03.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../include/board.h"

void set_console_title()
{
    SetConsoleTitle("Reversi");
}

void render_field(int status)
{
    printf(" %d  ", status);
}

struct Coord input_move(int player)
{
    printf("It's player %d's turn!\n\n", player);
    char x, y;
    printf("Enter X: ");
    fflush(stdin);
    scanf("%c", &x);
    printf("Enter Y: ");
    fflush(stdin);
    scanf("%c", &y);
    struct Coord move;
    move.x = (int) (x - 'A');
    move.y = (int) (y - '1');

    return move;
}

void render_pass(int player)
{
    printf("Player %d had to pass.\n\n", player);
    fflush(stdin);
    char c;
    scanf("%c", &c);
}

void render_game_over(int score_1, int score_2)
{
    printf("\n\nGAME OVER!\n\n");
    if (score_1 > score_2) {
        printf("Victory: Player One won with %d to %d points!", score_1, score_2);
    } else if (score_1 < score_2) {
        printf("Victory: Player Two won with %d to %d points!", score_2, score_1);
    } else {
        printf("Draw: Both Players are tied with %d points!", score_1);
    }

}

/**
 * renders a given board on the console (including axis-labeling)
 * @param board: Pointer to a Board
 */
void render_board(struct Board *board)
{
    // Labeling for x- and y-axis
    char x_axis[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char y_axis[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    // Column labeling
    printf("  |");
    for (int x=0; x < 8; x++) {
        printf(" %c |", x_axis[x]);
    }
    printf("\n--+--------------------------------\n");

    // Iterate rows
    for (int x = 0; x < 8; x++) {
        // Row Labeling
        printf("%c |", y_axis[x]);
        // Iterate colums
        for (int y = 0; y < 8; y++) {
            render_field(board->fields[x][y]);
        }
        printf("\n--|                                \n");
    }
}

void render_time(int seconds)
{
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int hours = minutes / 60;
    minutes = minutes % 60;
    printf("\nTime: %02d:%02d:%02d\n", hours, minutes, seconds);
}

void render_score(int score_1, int score_2)
{
    printf("\nScore: %d:%d\n\n", score_1, score_2);
}
