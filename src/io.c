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
#include <conio.h>
#include "../include/board.h"

#define TCRSS_RGHT 185
#define EDGE_VRTCL 186
#define CRNR_TP_RGHT 187
#define CRNR_BTM_RGHT 188
#define CRNR_BTM_LFT 200
#define CRNR_TP_LFT 201
#define TCRSS_BTM 202
#define TCRSS_TP 203
#define TCRSS_LEFT 204
#define EDGE_HRZNTL 205
#define CRSS_CNTR 206
#define PLR_ONE 177
#define PLR_TWO 219
#define CRSR 220

#define INPT_UP 72
#define INPT_DWN 80
#define INPT_LFT 75
#define INPT_RGHT 77
#define INPT_ENTR 13
#define INPT_PSE 112

const char x_axis[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
const char y_axis[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

void set_console_title()
{
    SetConsoleTitle("Reversi");
}

void render_field(int status)
{
    printf(" %d  ", status);
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

void render(struct Board *board, int seconds, struct Coord cursor)
{
    int score_one = count_points(board, 1);
    int score_two = count_points(board, 2);
    int minutes = seconds / 60;
    seconds = seconds % 60;
    int hours = minutes / 60;
    minutes = minutes % 60;

    system("cls");

    printf("                                                  \n");
    printf("          - - - R E V E R S I - - -               \n");
    printf("                                                  \n");
    printf(" Score: %2d:%-2d                   Time: %02d:%02d:%02d    \n", score_one, score_two, hours, minutes, seconds);
    printf("                                                  \n");
    printf("                                                  \n");
    printf("       ");
    for (int i = 0; i < 8; i++) {
        printf("  %c ", x_axis[i]);
    }
    printf("              \n");
    for (int x = 0; x < 9; x++) {
        if (x == 0) {
            // First line of board
            printf("       %c", CRNR_TP_LFT);
            for (int i = 0; i < 7; i++) {
                printf("%c%c%c%c", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, TCRSS_TP);
            }
            printf("%c%c%c%c          \n", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, CRNR_TP_RGHT);
        } else if (x == 8) {
            // Last line of board
            printf("       %c", CRNR_BTM_LFT);
            for (int i = 0; i < 7; i++) {
                printf("%c%c%c%c", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, TCRSS_BTM);
            }
            printf("%c%c%c%c          \n", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, CRNR_BTM_RGHT);
            break; // Don't print a line of fields after the last line
        } else {
            // Lines in between
            printf("       %c", TCRSS_LEFT);
            for (int i = 0; i < 7; i++) {
                printf("%c%c%c%c", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, CRSS_CNTR);
            }
            printf("%c%c%c%c          \n", EDGE_HRZNTL, EDGE_HRZNTL, EDGE_HRZNTL, TCRSS_RGHT);
        }
        printf("     %c %c ", y_axis[x], EDGE_VRTCL);
        for (int y = 0; y < 8; y++) {
            char field = ' ';
            if (board->fields[x][y] == 1) {
                field = PLR_ONE;
            } else if (board->fields[x][y] == 2) {
                field = PLR_TWO;
            }
            if (cursor.x == x && cursor.y == y) {
                field = CRSR;
            }
            printf("%c", field);
            printf(" %c ", EDGE_VRTCL);
        }
        printf("         \n");
    }
    printf("                                                  \n");
}

struct Coord input_move(struct Board *board, int seconds, int player, struct Coord cursor)
{
    printf("It's player %d's turn!\n\n", player);

    while(1) {
        switch(getch()) {
            case INPT_UP:
                cursor.x--;
                if (cursor.x < 0) {
                    cursor.x = 0;
                }
                break;
            case INPT_DWN:
                cursor.x++;
                if (cursor.x > 7) {
                    cursor.x = 7;
                }
                break;
            case INPT_RGHT:
                cursor.y++;
                if (cursor.y > 7) {
                    cursor.y = 7;
                }
                break;
            case INPT_LFT:
                cursor.y--;
                if (cursor.y < 0) {
                    cursor.y = 0;
                }
                break;
            case INPT_PSE:
                printf("paused");
            case INPT_ENTR:
                return cursor;
        }

        render(board, seconds, cursor);
    }
}
