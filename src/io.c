/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian G�rres, Fabian Heeke
 * Date: 03.04.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"

/**
 * renders a given board on the console (including axis-labeling)
 * @param board: Pointer to a Board
 */
void render_board(struct Board *board)
{
    // Labeling for x- and y-axis
    char x_axis[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    char y_axis[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    // Column labeling
    printf("  |");
    for (int x=0; x < 8; x++) {
        printf(" %d |", x_axis[x]);
    }
    printf("\n");

    // Iterate rows
    for (int y=0; y < 8; y++) {
        // Row Labeling
        printf("%d |",y_axis[y]);
        // Iterate colums
        for (int x = 0; x < 8; x++) {
            printf(" %d  ", board->fields[y][x]);
        }
        printf("\n");
    }
}
