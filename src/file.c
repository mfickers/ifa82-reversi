/**
 * File-Handling for saving the current game-state
 *
 * Author: Maximilian Fickers, Julian Görres, Fabian Heeke
 * Date: 09.05.2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/board.h"
#include "../include/file.h"

// TODO: Add Timer
// Source: https://stackoverflow.com/a/9840678
int save_file(struct Board *board, int player, int seconds)
{
    // open file (creates file, if file is not existing yet)
    FILE *file = fopen("Reversi.txt", "w");

    // add board to file
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            fprintf(file, "%d", board->fields[x][y]);
        }
        fprintf(file,"\n");
    }
    //add player to file
    fprintf(file, "%d\n", player);
    //add timer to file
    fprintf(file, "%d\n", seconds);

    fclose(file);
}
/**
 * @param filename  name of the savestate to be loaded
 */
struct Savestate get_savestate()
{
    printf("Opening file..\n");
    // open file (creates file, if file is not there)
    FILE *file = fopen("Reversi.txt", "r");

    struct Savestate savestate;

    // set variables for file-parsing
    char time_string[100];
    int line_counter = 0;
    int char_counter = 0;
    char file_char;
    // read file character by character and stop when end is reached
    while((file_char = fgetc(file)) != EOF) {

        // if in the first 7 lines, get board info
        if(line_counter <= 7 && file_char != '\n'){
            // get board-values line-by-line from file
            savestate.board.fields[line_counter][char_counter] = file_char - '0';
            char_counter++;
        // if above first 7 lines, get remaining info
        }else if(line_counter > 7 && file_char != '\n'){

            switch(line_counter){
                case 8: {
                    // get player-value from file
                    savestate.player = file_char - '0';
                }
                case 9:{
                    // get timer-values from file
                    time_string[char_counter]  = file_char;
                    char_counter++;
                }
            }
        // when new_line, increase line-counter and reset char_counter
        }else if(file_char == '\n'){
            line_counter++;
            char_counter = 0;
            continue;
        }
    }
    // set safestate timer by changing time-string to integer and casting it to time_t
    savestate.timer = (time_t)atoi(time_string);

    return savestate;

}
