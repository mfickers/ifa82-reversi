/**
 * Represents the Input and Output Functions for a Reversi-Game
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
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
    char x_axis[8] = {1,2,3,4,5,6,7,8};
    char y_axis[8] = {1,2,3,4,5,6,7,8};

    // y representing the lines
    for(int y=0; y < 9; y++){
        printf("\n");

        // print x axis for first line
        if(y == 0){
            printf("  |");
            for(int x=0; x < 8; x++){
                printf(" %d |", x_axis[x]);
            }
        }
        // print y-axis and board for rest
        else{
            printf("%d |",y_axis[y-1]); // -1 because first line is reserved for x-axis-labeling
            // x representing the column of each line
            for(int x = 0; x < 8; x++){
                printf(" %d  ", board->fields[y-1][x]);
            }
        }
    }
    printf("\n"); // for overview
}
